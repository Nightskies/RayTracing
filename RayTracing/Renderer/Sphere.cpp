#include "Sphere.h"


Sphere::Sphere(const glm::vec3& center, f32 radius)
	:
	mCenter(center),
	mRadius(radius)
{}

bool Sphere::Hit(LightRay& r) const
{
	glm::vec3 sc = r.StartPos - mCenter;
	f32 a = glm::dot(r.Direction, r.Direction);
	f32 halfB = glm::dot(r.Direction, sc);
	f32 c = glm::dot(sc, sc) - mRadius * mRadius;
	f32 d = halfB * halfB - a * c; 

	return d > 0.0f;
}