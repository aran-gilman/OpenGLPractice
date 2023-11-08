#include "PointLight.h"

#include <stdexcept>

#include <GL/glew.h>

#include "../Object.h"
#include "Transform.h"

PointLight::PointLight(Object* owner, float strength, Color color, float attenuation) :
	Component(owner),
	strength(strength),
	color(color),
	attenuation(attenuation),
	transform(owner->GetComponent<Transform>())
{
	if (transform == nullptr)
	{
		throw std::runtime_error("MeshRenderer construction failed: owning object does not have a Transform component");
	}
}

void PointLight::Use(unsigned int bufferID)
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 4 * sizeof(float), &color);
	glm::vec3 position = transform->GetPosition();
	glBufferSubData(GL_UNIFORM_BUFFER, 32, 4 * sizeof(float), &position);
	glBufferSubData(GL_UNIFORM_BUFFER, 48, sizeof(float), &attenuation);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
