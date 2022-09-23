#include "Shader.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

const char* VERTEX_SHADER_EXTENSION = ".vt";
const char* FRAGMENT_SHADER_EXTENSION = ".fg";

Shader::Shader(std::filesystem::path&& vertShaderPath, std::filesystem::path&& fragShaderPath)
{
	std::string fragShaderSrc = GetSource(std::move(fragShaderPath));
	std::string vertShaderSrc = GetSource(std::move(vertShaderPath));

	u32 vertShader = glCreateShader(GL_VERTEX_SHADER);
	u32 fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	u32 program = glCreateProgram();

	const char* srcPtr = vertShaderSrc.c_str();
	glShaderSource(vertShader, 1, &srcPtr, nullptr);
	Compile(vertShader);
	glAttachShader(program, vertShader);

	srcPtr = fragShaderSrc.c_str();
	glShaderSource(fragShader, 1, &srcPtr, nullptr);
	Compile(fragShader);
	glAttachShader(program, fragShader);

	Link(program);

	glDetachShader(program, vertShader);
	glDetachShader(program, fragShader);

	mID = program;
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& val)
{
	glUniformMatrix4fv(GetUniformLoaction(name), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::SetUniformInt(const std::string& name, const int val)
{
	glUniform1i(GetUniformLoaction(name), val);
}

void Shader::SetUniformFloat1(const std::string& name, const f32 val)
{
	glUniform1f(GetUniformLoaction(name), val);
}

void Shader::SetUniformFloat4(const std::string& name, const glm::vec4& val)
{
	glUniform4f(GetUniformLoaction(name), val.x, val.y, val.z, val.w);
}

void Shader::SetUniformFloat3(const std::string& name, const glm::vec3& val)
{
	glUniform3f(GetUniformLoaction(name), val.x, val.y, val.z);
}

void Shader::Use() const
{
	glUseProgram(mID);
}

std::string Shader::GetSource(std::filesystem::path&& shaderFile)
{
	if (shaderFile.has_extension())
	{
		std::string extension = shaderFile.extension().string();

		if (extension == FRAGMENT_SHADER_EXTENSION ||
			extension == VERTEX_SHADER_EXTENSION)
		{
			std::ifstream file(shaderFile);
			std::stringstream ss;

			if (file)
			{
				ss << file.rdbuf();
			}
			else
			{
				std::cerr << "Error: file " << shaderFile.string() << " wasn't opened\n";
			}

			return ss.str();
		}
		else
		{
			std::cerr << "Error: file " << shaderFile.string() << " has invalid extension\n";
		}
	}
	else
	{
		std::cerr << "Error: file " << shaderFile.string() << " hasn't extension\n";
	}
}

void Shader::Compile(u32 shader)
{
	s32 result;

	glCompileShader(shader);
	if (glGetShaderiv(shader, GL_COMPILE_STATUS, &result); result == GL_FALSE)
	{
		s32 length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string msg("", length);
		glGetShaderInfoLog(shader, length, &length, msg.data());

		std::cerr << "Compile error: " << msg;

		glDeleteShader(shader);
	}
}

void Shader::Link(u32 program)
{
	s32 result;

	glLinkProgram(program);

	if (glGetProgramiv(program, GL_LINK_STATUS, &result); result == GL_FALSE)
	{
		s32 length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		std::string msg("", length);
		glGetProgramInfoLog(program, length, &length, msg.data());

		std::cerr << "Link error: " << msg;

		glDeleteShader(program);
	}
}

s32 Shader::GetUniformLoaction(const std::string& name)
{
	if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
		return mUniformLocationCache[name];

	s32 location = glGetUniformLocation(mID, name.c_str());

	if (location == -1)
	{
		std::cerr << "Warning: uniform " << name << " doesn't exist\n";
	}
	else
	{
		mUniformLocationCache[name] = location;
	}

	return location;
}

Shader::~Shader()
{
	glDeleteProgram(mID);
}