#include "Camera.h"

Camera::Camera(f32 aspectRatio, f32 fov, const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3& worldUp)
	:
	mFOV(fov),
	mAspectRatio(aspectRatio)
{
	mW = glm::normalize(lookfrom - lookat);
	mU = glm::normalize(glm::cross(worldUp, mW));
	mV = glm::cross(mW, mU);

	mPosition = lookfrom;
	mXAxis = mViewportWidth * mU;
	mYAxis = mViewportHeight * mV;
	mLowerLeftCorner = mPosition - mXAxis * 0.5f - mYAxis * 0.5f - mW;
}

LightRay Camera::GetRay(f32 u, f32 v) const
{
	return { mPosition, mLowerLeftCorner + u * mXAxis + v * mYAxis - mPosition };
}