#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <memory>

#include "Component.h"
#include "../Event.h"

class Material;
class Mesh;
class Object;
class Transform;

class MeshRenderer : public Component
{
public:
	MeshRenderer(Object* owner, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
	~MeshRenderer() override;

private:
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;

	Transform* transform;

	EventHandle renderEventHandle;

	void HandleRender(double elapsedTime);
};

#endif

