#include "Camera.h"
#include "Hittable.h"

#include <vector>

class Scene
{
public:
	Scene();

	void AddObj(HittableObjects&& obj);

	glm::vec3 ShootRay(f32 u, f32 v) const;
	bool Hit(LightRay& r) const;

	static UPtr<Scene> Create() { return std::make_unique<Scene>(); }
private:
	UPtr<Camera> mCamera;

	std::vector<HittableObjects> mObjects;
};