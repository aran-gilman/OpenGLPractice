#include "MeshRenderer.h"

#include <functional>
#include <stdexcept>

#include "../Game.h"
#include "../Material.h"
#include "../Mesh.h"
#include "../Object.h"
#include "../Shader.h"
#include "Transform.h"

MeshRenderer::MeshRenderer(Object* owner, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) :
	Component(owner),
	mesh(mesh),
	material(material),
	transform(owner->GetComponent<Transform>()),
	renderEventHandle(owner->GetGame()->OnRender().Register(std::bind_front(&MeshRenderer::HandleRender, this)))
{
	if (transform == nullptr)
	{
		throw std::runtime_error("MeshRenderer construction failed: owning object does not have a Transform component");
	}
}

MeshRenderer::~MeshRenderer()
{
	GetOwner()->GetGame()->OnRender().Unregister(renderEventHandle);
}

void MeshRenderer::HandleRender(double elapsedTime)
{
	material->Use();
	material->GetShader()->SetMatrix4("transform", transform->GetMatrixPtr());
	material->GetShader()->SetMatrix3("normalMatrix", transform->GetNormalMatrixPtr());
	mesh->Draw();
	material->Reset();
}
