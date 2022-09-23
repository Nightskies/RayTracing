#pragma once
#include "Types.h"

struct GLFWwindow;

class Window
{
private:
	GLFWwindow* mHandle;

	std::pair<s32, s32> mDimensions;
public:
	Window(std::pair<s32, s32>&& dimensions);
	~Window();

	GLFWwindow* GetNativeWindow() const { return mHandle; }
	const std::pair<s32, s32>& GetDimensions() const { return mDimensions; }

	void Update();

	void BindContext();
	void UnbindContext();

	bool IsClosed();

	static UPtr<Window> Create(std::pair<s32, s32>&& dimensions) { return std::make_unique<Window>(std::move(dimensions)); }
};