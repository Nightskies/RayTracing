#pragma once
#include "LightRay.h"

class Camera
{
public:
	Camera(f32 aspectRatio, f32 fov, f32 fd, f32 aperture, const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3& worldUp);

	LightRay GetRay(f32 u, f32 v) const;

	template<typename... Args>
	static UPtr<Camera> Create(Args... args) { return std::make_unique<Camera>(std::forward<Args>(args)...); }
private:
	f32 mFOV;
	f32 mAspectRatio;

	f32 mViewportHeight, mViewportWidth;

	f32 mFocusDist;
	f32 mLensRadius;

	glm::vec3 mPosition;
	glm::vec3 mXAxis;
	glm::vec3 mYAxis;
	glm::vec3 mLowerLeftCorner;

	glm::vec3 mW;
	glm::vec3 mU;
	glm::vec3 mV;
};