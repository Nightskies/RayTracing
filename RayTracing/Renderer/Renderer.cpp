#include "Renderer.h"
#include "RenderCommand.h"


Renderer::Renderer(const SPtr<Window>& win)
	:
	mPixelBuffer(Config::sImageHeight * Config::sImageWidth),
	mImageHeight(Config::sImageHeight),
	mImageWidth(Config::sImageWidth),
	mWindow(win)
{
	mShader = Shader::Create("Res/Shaders/Basic.vt", "Res/Shaders/Basic.fg");
	mPool = ThreadPool::Create();
	mScene = Scene::Create();

	RenderCommand::Init();
	RenderCommand::Viewport(Config::sWindowWidth, Config::sWindowHeight);

	mVBO = VBO::Create(mPixelBuffer.size() * sizeof(Pixel));
	UPtr<VAO> mVAO = VAO::Create();
	mVAO->AddVBO(mVBO);
	mShader->Use();
}

void Renderer::Update()
{
	mState = Details::match(mState,
		[this](RenderState::Begin& state) -> Renderer::State
		{
			mWindow->UnbindContext();

			for (s32 i = 0; i < mPool->mNumThreads; i++)
			{
				mPool->mThreads.push_back(std::thread([this, i](){ RayTracing(i); }));
			}

			for (auto& th : mPool->mThreads)
			{
				th.detach();
			}

			return RenderState::Draw{};
		},
		[this](RenderState::Draw& state) -> Renderer::State
		{
			if (!mPool->IsWorkCompleted())
			{
				std::unique_lock lk(mPool->sCVMutex);
				mPool->sCV.wait(lk, [this]() { return ThreadPool::IsLineProcessed(); });

				mWindow->BindContext();
				RenderCommand::ClearColor();
				RenderCommand::ClearBuffers();
				RenderCommand::DrawPixels(mPixelBuffer.size());
				mWindow->Update();
				mWindow->UnbindContext();

				mPool->sLineProcessed = false;

				return RenderState::Draw{};
			}
			else
			{
				mWindow->BindContext();
				return RenderState::End{};
			}

		},
		[this](RenderState::End& state) -> Renderer::State
		{
			RenderCommand::ClearColor();
			RenderCommand::ClearBuffers();
			RenderCommand::DrawPixels(mPixelBuffer.size());
			mWindow->Update();

			return RenderState::End{};
		}
	);
}

void Renderer::RayTracing(u32 threadIndex)
{
	s32 y, x;
	for (y = mImageHeight - threadIndex - 1; y >= 0; y -= mPool->mNumThreads)
	{
		s32 l = mImageHeight - y - 1;
		for (x = 0; x < mImageWidth; x++)
		{
			glm::vec3 pixelColor(0.0f, 0.0f, 0.0f);
			for (s32 s = 0; s < Config::sSamplesPerPixel; s++)
			{
				f32 u = f32(x + Utils::random()) / (mImageWidth - 1);
				f32 v = f32(y + Utils::random()) / (mImageHeight - 1);
				pixelColor += mScene->ShootRay(u, v);
			}

			mPixelBuffer[l * mImageWidth + x].Pos = { f32(x) / (mImageWidth - 1) - 0.5f, f32(y) / (mImageHeight - 1) - 0.5f, 0.0f };
			mPixelBuffer[l * mImageWidth + x].Color = pixelColor * Config::sScale;
		}

		{
			std::lock_guard lk(mPool->sCVMutex);

			mWindow->BindContext();
			mVBO->SetData(reinterpret_cast<const void*>(&mPixelBuffer[l * mImageWidth]), mImageWidth * sizeof(Pixel), l * mImageWidth * sizeof(Pixel));
			mWindow->UnbindContext();

			mPool->sLineProcessed = true;
		}
		mPool->sCV.notify_one();
	}
	++mPool->sNumCompletedThreads;
}