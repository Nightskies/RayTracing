#pragma once
#include "LightRay.h"

class Camera
{
public:
	Camera(f32 aspectRatio, f32 fov, const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3& worldUp);

	LightRay GetRay(f32 u, f32 v) const;

	template<typename... Args>
	static UPtr<Camera> Create(Args... args) { return std::make_unique<Camera>(std::forward<Args>(args)...); }
private:
	f32 mFOV;
	f32 mAspectRatio;

	f32 h = glm::tan(glm::radians(mFOV) / 2.0f);
	f32 mViewportHeight = 2.0f;
	f32 mViewportWidth = mAspectRatio * mViewportHeight;

	glm::vec3 mPosition = { 0.0f, 0.0f, 0.0f };
	glm::vec3 mXAxis = { mViewportWidth, 0.0f, 0.0f };
	glm::vec3 mYAxis = { 0.0f, mViewportHeight, 0.0f };
	glm::vec3 mFocalPoint = { 0.0f, 0.0f, 1.0f };
	glm::vec3 mLowerLeftCorner = mPosition - mXAxis * 0.5f - mYAxis * 0.5f - mFocalPoint;

	glm::vec3 mW;
	glm::vec3 mU;
	glm::vec3 mV;
};