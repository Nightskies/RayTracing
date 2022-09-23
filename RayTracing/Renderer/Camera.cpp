#include "Camera.h"

Camera::Camera(f32 aspectRatio, f32 fov, f32 fd, f32 aperture, const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3& worldUp)
	:
	mAspectRatio(aspectRatio),
	mFOV(fov),
	mFocusDist(fd),
	mLensRadius(aperture / 2.0f)
{
	mW = glm::normalize(lookfrom - lookat);
	mU = glm::normalize(glm::cross(worldUp, mW));
	mV = glm::cross(mW, mU);

	mViewportHeight = 2.0f * glm::tan(glm::radians(mFOV) / 2.0f);
	mViewportWidth = mAspectRatio * mViewportHeight;

	mPosition = lookfrom;
	mXAxis = mFocusDist * mViewportWidth * mU;
	mYAxis = mFocusDist * mViewportHeight * mV;
	mLowerLeftCorner = mPosition - mXAxis * 0.5f - mYAxis * 0.5f - mFocusDist * mW;
}

LightRay Camera::GetRay(f32 u, f32 v) const
{
	glm::vec3 rd = mLensRadius * Utils::random_in_unit_sphere();
	glm::vec3 offset = mU * rd.x + mV * rd.y;
	return { mPosition + offset, mLowerLeftCorner + u * mXAxis + v * mYAxis - mPosition - offset };
}