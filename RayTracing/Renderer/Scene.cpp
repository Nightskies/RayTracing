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
	{
		glm::vec3 normal = glm::normalize(r.At(r.Root) - glm::vec3(0.0f, 0.0f, -1.0f));
		return 0.5f * glm::vec3(normal.x + 1.0f, normal.y + 1.0f, normal.z + 1.0f);
	}

	glm::vec3 unitDir = glm::normalize(r.Direction);
	f32 t = 0.5f * (unitDir.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}