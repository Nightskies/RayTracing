#include "Scene.h"

#include "Core/Config.h"

Scene::Scene()
	:
	mSphere({ 0.0f, 0.0f, -1.0f }, 0.5f)
{
	mCamera = Camera::Create(Config::sAspectRatio);
}

glm::vec3 Scene::ShootRay(f32 u, f32 v) const
{
	LightRay r = mCamera->GetRay(u, v);

	if (mSphere.Hit(r))
		return { 1.0f, 0.0f, 0.f };

	glm::vec3 unitDir = glm::normalize(r.Direction);
	f32 t = 0.5f * (unitDir.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}