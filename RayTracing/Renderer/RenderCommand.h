#pragma once
#include "Core/Types.h"

class RenderCommand
{
public:
	static void Init();

	static void ClearBuffers();

	static void ClearColor();

	static void Viewport(s32 width, s32 height);

	static void DrawPixels(s32 count);
};