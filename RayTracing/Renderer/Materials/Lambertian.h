#pragma once
#include "Core/Utils.h"

class LightRay;

class Lambertian
{
public:
    Lambertian() = default;
    Lambertian(const glm::vec3& albedo);

    std::optional<glm::vec3> Diffusion(LightRay& r) const;
public:
    glm::vec3 mAlbedo;
};

