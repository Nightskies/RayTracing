#include "Scene.h"

#include "Core/Config.h"

Scene::Scene()
{
	mCamera = Camera::Create(Config::sAspectRatio, 20.0f, 10.f, 0.1f, glm::vec3(13.0f, 2.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	auto&& groundMaterial = Lambertian({ 0.5f, 0.5f, 0.5f });
	AddObj(Sphere({ 0.0f, -1000.0f, 0.0f }, 1000.0f, std::move(groundMaterial)));

	for (s32 a = -11; a < 11; a++)
	{
		for (s32 b = -11; b < 11; b++)
		{
			auto chooseMat = Utils::random();
			glm::vec3 center(a + 0.9f * Utils::random(), 0.2f, b + 0.9f * Utils::random());

			if (glm::length((center - glm::vec3(4.0f, 0.2f, 0.0f))) > 0.9f)
			{
				if (chooseMat < 0.8)
				{
					// diffuse
					auto albedo = Utils::get_random_vector() * Utils::get_random_vector();
					auto&& sphereMaterial = Lambertian(albedo);
					AddObj(Sphere(center, 0.2f, std::move(sphereMaterial)));
				}
				else if (chooseMat < 0.95)
				{
					// metal
					auto albedo = Utils::get_random_vector(0.5f, 1.0f);
					auto fuzz = Utils::random(0.0f, 0.5f);
					auto&& sphereMaterial = Metal(albedo, fuzz);
					AddObj(Sphere(center, 0.2f, std::move(sphereMaterial)));
				}
				else
				{
					// glass
					auto&& sphereMaterial = Dielectric(1.5f);
					AddObj(Sphere(center, 0.2f, std::move(sphereMaterial)));
				}
			}
		}
	}

	auto&& material1 = Dielectric(1.5f);
	AddObj(Sphere({ 0.0f, 1.0f, 0.0f }, 1.0f, std::move(material1)));

	auto&& material2 = Lambertian({ 0.4f, 0.2f, 0.1f });
	AddObj(Sphere({ -4.0f, 1.0f, 0.0f }, 1.0f, std::move(material2)));

	auto&& material3 = Metal({ 0.7f, 0.6f, 0.5f }, 0.0f);
	AddObj(Sphere({ 4.0f, 1.0f, 0.0f }, 1.0f, std::move(material3)));
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