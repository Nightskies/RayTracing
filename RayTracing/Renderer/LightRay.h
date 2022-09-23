#pragma once
#include "Materials/Materials.h"

class LightRay
{
public:
	LightRay() = default;
	LightRay(const glm::vec3& start, const glm::vec3& direction);

	glm::vec3 At(f32 t) const { return StartPos + t * Direction; }

	void SetFaceNormal();

	std::optional<glm::vec3> Scatter();
public:
	glm::vec3 StartPos;
	glm::vec3 Direction;

	glm::vec3 HitPos;
	glm::vec3 HitNormal;
	f32 MinRoot = 0.001f;
	f32 MaxRoot = INF;
	bool FrontFace;

	const Materials* Material;
};