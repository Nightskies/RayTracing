#include "Application.h"

#include <GLFW/glfw3.h>

Application::Application()
{
	mWindow = Window::Create({ Config::sWindowWidth, Config::sWindowHeight });
	mRenderer = Renderer::Create(mWindow);
}

Application::~Application()
{
	glfwTerminate();
}

void Application::Run()
{
	while (!mWindow->IsClosed())
	{
		mRenderer->Update();
	}
}
