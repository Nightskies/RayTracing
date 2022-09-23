#pragma once

#include "Renderer/Renderer.h"

class Application
{
public:
	Application();
	~Application();

	void Run();
private:
	SPtr<Window> mWindow;
	UPtr<Renderer> mRenderer;
};