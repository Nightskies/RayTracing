#pragma once
#include "Shader.h"
#include "VBO.h"
#include "VAO.h"

#include "Core/ThreadPool.h"
#include "Core/Window.h"
#include "Core/Utils.h"
#include "Core/Config.h" 

#include <glm/glm.hpp>

struct Pixel
{
	glm::vec3 Pos;
	glm::vec3 Color;
};

namespace RenderState
{
	class Begin
	{};

	class Draw
	{};

	class End
	{};
}

class Renderer
{
public:
	Renderer(const SPtr<Window>& win);
	~Renderer() = default;

	void RayTracing(u32 threadIndex);
	void Update();

	static UPtr<Renderer> Create(const SPtr<Window>& win) { return std::make_unique<Renderer>(win); }
private:
	using State = std::variant<RenderState::Begin, RenderState::Draw, RenderState::End>;
	State mState;

	UPtr<Shader> mShader;
	UPtr<ThreadPool> mPool;
	SPtr<Window> mWindow;

	SPtr<VBO> mVBO;

	std::vector<Pixel> mPixelBuffer;
	u32 mImageWidth, mImageHeight;
};