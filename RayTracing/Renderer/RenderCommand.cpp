#include "RenderCommand.h"

#include <glad/glad.h>

void RenderCommand::Init()
{

}

void RenderCommand::ClearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderCommand::ClearColor()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void RenderCommand::DrawPixels(s32 count)
{
	glDrawArrays(GL_POINTS, 0, count);
}

void RenderCommand::Viewport(s32 width, s32 height)
{
	glViewport(0, 0, width, height);
}
