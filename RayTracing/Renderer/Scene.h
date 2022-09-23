#include "Camera.h"

//#include "Core/Config.h"

class Scene
{
public:
	Scene();

	glm::vec3 ShootRay(f32 u, f32 v) const;

	static UPtr<Scene> Create() { return std::make_unique<Scene>(); }
private:
	UPtr<Camera> mCamera;
};

