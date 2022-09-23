#include "Dielectric.h"
#include "Renderer/LightRay.h"

Dielectric::Dielectric(f32 refraction)
    :
    mRefraction(refraction)
{}

std::optional<glm::vec3> Dielectric::Diffusion(LightRay& r) const
{
    glm::vec3 attenuation = { 1.0f, 1.0f, 1.0f };
    f32 refractionRatio = r.FrontFace ? (1.0f / mRefraction) : mRefraction;

    glm::vec3 unitDir = glm::normalize(r.Direction);
    f32 cosTheta = glm::min(glm::dot(-unitDir, r.HitNormal), 1.0f);
    f32 sinTheta = glm::sqrt(1.0f - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0f;
    glm::vec3 direction;

    if (cannotRefract || Reflectance(cosTheta, refractionRatio) > Utils::random())
        direction = glm::reflect(unitDir, r.HitNormal);
    else
        direction = glm::refract(unitDir, r.HitNormal, refractionRatio);

    r.StartPos = r.HitPos;
    r.Direction = direction;

    return attenuation;
}

f32 Dielectric::Reflectance(f32 cosine, f32 refraction) const
{
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - refraction) / (1 + refraction);
    r0 = r0 * r0;
    return r0 + (1 - r0) * glm::pow((1 - cosine), 5);
}