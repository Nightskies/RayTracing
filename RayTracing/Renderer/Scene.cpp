#include "Scene.h"

#include "Core/Config.h"

Scene::Scene()
{
	glm::vec3 lookfrom = { 3.0f, 3.0f, 2.0f };
	glm::vec3 lookat = { 0.0f, 0.0f, -1.0f };
	f32 focusDist = glm::length(lookfrom - lookat);
	mCamera = Camera::Create(Config::sAspectRatio, 20.0f, focusDist, 2.0f, lookfrom, lookat, glm::vec3(0.0f, 1.0f, 0.0f));

	auto&& materialGround = Lambertian({ 0.8f, 0.8f, 0.0f });
	auto&& materialCenter = Lambertian({ 0.1f, 0.2f, 0.5f });
	auto&& materialLeft1 = Dielectric(1.5f);
	auto&& materialLeft2 = Dielectric(1.5f);
	auto&& materialRight = Metal({ 0.8f, 0.6f, 0.2f }, 0.0f);

	AddObj(Sphere({ 0.0f, 0.0f, -1.0f }, 0.5f, std::move(materialCenter)));
	AddObj(Sphere({ 0.0f, -100.5f, -1.0f }, 100.0f, std::move(materialGround)));
	AddObj(Sphere({ -1.0f, 0.0f, -1.0f }, 0.5f, std::move(materialLeft1)));
	AddObj(Sphere({ -1.0f, 0.0f, -1.0f }, -0.4f, std::move(materialLeft2)));
	AddObj(Sphere({ 1.0f, 0.0f, -1.0f }, 0.5f, std::move(materialRight)));
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