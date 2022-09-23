#include "LightRay.h"

LightRay::LightRay(const glm::vec3& start, const glm::vec3& direction)
	:
	StartPos(start),
	Direction(direction)
{}

void LightRay::SetFaceNormal()
{
	if (FrontFace = glm::dot(Direction, HitNormal) < 0.0f; !FrontFace)
	{
		HitNormal = -HitNormal;
	}
}