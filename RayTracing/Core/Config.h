#pragma once
#include "Types.h"

class Config
{
public:
	inline static constexpr s32 sWindowWidth = 1280;
	inline static constexpr s32 sWindowHeight = 720;

	inline static constexpr f32 sAspectRatio = 16.0f / 9.0f;

	inline static constexpr u32 sImageWidth = 1200u;
	inline static constexpr u32 sImageHeight = static_cast<u32>(sImageWidth / sAspectRatio);

	inline static constexpr u32 sSamplesPerPixel = 32u;
	inline static constexpr f32 sScale = 1.0f / sSamplesPerPixel;
	inline static constexpr u32 sDepth = 8u;
};