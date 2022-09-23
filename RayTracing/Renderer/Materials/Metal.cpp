#include "Metal.h"

#include "Renderer/LightRay.h"

Metal::Metal(const glm::vec3& albedo, f32 f)
    :
    mAlbedo(albedo),
    mFuzz(f < 1 ? f : 1)
{}

std::optional<glm::vec3> Metal::Diffusion(LightRay& r) const
{
    glm::vec3 reflected = glm::reflect(glm::normalize(r.Direction), r.HitNormal);
    r.StartPos = r.HitPos;
    r.Direction = reflected + mFuzz * Utils::random_in_unit_sphere();;

    if (glm::dot(r.Direction, r.HitNormal) > 0)
    {
        return mAlbedo;
    }

    return std::nullopt;
}
