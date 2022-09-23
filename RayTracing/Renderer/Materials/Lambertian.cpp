#include "Lambertian.h"
#include "Renderer/LightRay.h"


Lambertian::Lambertian(const glm::vec3& albedo)
    :
    mAlbedo(albedo)
{}

std::optional<glm::vec3> Lambertian::Diffusion(LightRay& r) const
{
    auto diffusionDir = r.HitNormal + Utils::random_unit_vector();

    if (Utils::near_zero_vector(diffusionDir))
    {
        diffusionDir = r.HitNormal;
    }

    r.StartPos = r.HitPos;
    r.Direction = diffusionDir;

    return mAlbedo;
}
