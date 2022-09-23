#pragma once
#include "LightRay.h"

class Sphere
{
public:
	Sphere() = default;
	Sphere(const glm::vec3& center, f32 radius, Materials&& material);

	bool Hit(LightRay& r) const;
private:
	glm::vec3 mCenter;
	f32 mRadius;
	Materials mMaterial;
};