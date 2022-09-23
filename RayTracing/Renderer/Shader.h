#pragma once
#include "Core/Types.h"

#include <filesystem>

#include <glm/glm.hpp>
#include <unordered_map>

class Shader
{
public:
	Shader(std::filesystem::path&& vertShaderPath, std::filesystem::path&& fragShaderPath);
	~Shader();

	void SetUniformMat4(const std::string& name, const glm::mat4& val);
	void SetUniformInt(const std::string& name, const int val);
	void SetUniformFloat1(const std::string& name, const f32 val);
	void SetUniformFloat4(const std::string& name, const glm::vec4& val);
	void SetUniformFloat3(const std::string& name, const glm::vec3& val);

	void Use() const;

	template<typename... Args>
	static UPtr<Shader> Create(Args... args) { return std::make_unique<Shader>(std::forward<Args>(args)...); }
private:
	std::string GetSource(std::filesystem::path&&);
	void Compile(u32 shader);
	void Link(u32 program);
	s32 GetUniformLoaction(const std::string& name);
private:
	u32 mID;
	std::unordered_map<std::string, s32> mUniformLocationCache;
};



