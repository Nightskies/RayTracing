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
	
	if (f32 d = halfB * halfB - a * c; d > 0.0f)
	{
		f32 t = (-halfB - glm::sqrt(d)) / a;
		if (t < r.MinRoot || t > r.MaxRoot)
		{
			if (t = (-halfB + glm::sqrt(d)) / a; t < r.MinRoot || t > r.MaxRoot)
			{
				return false;
			}
		}

		r.MaxRoot = t;
		r.HitPos = r.At(r.MaxRoot);
		r.HitNormal = (r.HitPos - mCenter) / mRadius;
		r.SetFaceNormal();

		return true;
	}
	else
	{
		return false;
	}
}