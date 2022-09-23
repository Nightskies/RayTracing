#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(std::pair<s32, s32>&& winProps)
	:
	mDimensions(std::move(winProps))
{
	if (s32 success = glfwInit(); !success)
	{
		std::cerr << "glfwInit error\n";
	}

	auto&& GLFWErrorCallback = [](s32 error, const char* description)
	{
		std::cerr << "GLFW Error (" << error << "):" << description << std::endl;
	};

	glfwSetErrorCallback(std::move(GLFWErrorCallback));

	auto [width, height] = mDimensions;

	if (mHandle = glfwCreateWindow(width, height, "RayTracing", nullptr, nullptr); !mHandle)
	{
		std::cerr << "glfwCreateWindow error\n";
	}

	glfwMakeContextCurrent(mHandle);

	if (s32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); !status)
	{
		std::cerr << "gladLoadGLLoader error\n";
	}

	glfwSwapInterval(0);
}

void Window::Update()
{
	glfwSwapBuffers(mHandle);
	glfwPollEvents();
}

void Window::BindContext()
{
	glfwMakeContextCurrent(mHandle);
}

void Window::UnbindContext()
{
	glfwMakeContextCurrent(nullptr);
}

bool Window::IsClosed()
{
	return glfwWindowShouldClose(mHandle);
}

Window::~Window()
{
	glfwDestroyWindow(mHandle);
}