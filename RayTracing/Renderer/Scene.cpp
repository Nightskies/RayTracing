#include "Scene.h"

#include "Core/Config.h"

Scene::Scene()
{
	mCamera = Camera::Create(Config::sAspectRatio);

	AddObj(Sphere({ 0.0f, 0.0f, -1.0f }, 0.5f));
	AddObj(Sphere({ 0.0f, -100.5f, -1.0f }, 100.0f));
}

void Scene::AddObj(HittableObjects&& obj)
{
	mObjects.emplace_back(std::move(obj));
}

bool Scene::Hit(LightRay& r) const
{
	bool IsAnythingHit = false;

	r.MaxRoot = INF;

	for (const auto& el : mObjects)
	{
		if (std::visit([&](const auto& object) { return object.Hit(r); }, el))
		{
			IsAnythingHit = true;
		}
	}

	return IsAnythingHit;
}

glm::vec3 Scene::ShootRay(f32 u, f32 v) const
{
	LightRay r = mCamera->GetRay(u, v);

	if (Hit(r))
	{
		return 0.5f * (r.HitNormal + 1.0f);
	}

	glm::vec3 unitDir = glm::normalize(r.Direction);
	f32 t = 0.5f * (unitDir.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}