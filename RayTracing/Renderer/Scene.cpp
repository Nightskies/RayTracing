#include "Scene.h"

#include "Core/Config.h"

Scene::Scene()
{
	mCamera = Camera::Create(Config::sAspectRatio);

	auto&& materialGround = Lambertian({ 0.8f, 0.8f, 0.0f });
	auto&& materialCenter = Lambertian({ 0.7f, 0.3f, 0.3f });

	AddObj(Sphere({ 0.0f, 0.0f, -1.0f }, 0.5f, std::move(materialCenter)));
	AddObj(Sphere({ 0.0f, -100.5f, -1.0f }, 100.0f, std::move(materialGround)));
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

	std::vector<glm::vec3> attenuations;
	glm::vec3 color = { 0.0f, 0.0f, 0.0f };

	bool isScattered = false;

	for (s32 depthCounter = 1; depthCounter != Config::sDepth && Hit(r); ++depthCounter)
	{
		if (auto attenuation = r.Scatter())
		{
			isScattered = true;
			attenuations.emplace_back(std::move(*attenuation));
			continue;
		}

		return color;
	}

	glm::vec3 unitDir = glm::normalize(r.Direction);
	f32 t = 0.5f * (unitDir.y + 1.0f);
	color = (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);

	if (isScattered)
	{
		for (auto&& a : attenuations)
		{
			color *= std::move(a);
		}
	}

	return color;
}