#pragma once
#include "Core/Types.h"

#include <glm/glm.hpp>

class LightRay
{
public:
	LightRay() = default;
	LightRay(const glm::vec3& start, const glm::vec3& direction);

	glm::vec3 At(f32 t) const { return StartPos + t * Direction; }

public:
	glm::vec3 StartPos;
	glm::vec3 Direction;

	f32 Root;
};