#pragma once
#include "Core/Utils.h"

class LightRay;

class Metal
{
public:
    Metal() = default;
    Metal(const glm::vec3& albedo, f32 f);

    std::optional<glm::vec3> Diffusion(LightRay& r) const;
public:
    glm::vec3 mAlbedo;
    f32 mFuzz;
};