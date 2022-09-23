#pragma once
#include "Core/Utils.h"

class LightRay;

class Dielectric
{
public:
    Dielectric() = default;
    Dielectric(f32 refraction);

    std::optional<glm::vec3> Diffusion(LightRay& r) const;
private:
    f32 Reflectance(f32 cosine, f32 refraction) const;
public:
    f32 mRefraction; // Index of Refraction
};