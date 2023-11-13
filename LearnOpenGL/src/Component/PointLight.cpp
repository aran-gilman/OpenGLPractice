#include "PointLight.h"

#include <stdexcept>

#include <GL/glew.h>

#include "../Object.h"
#include "Transform.h"

PointLight::PointLight(Object* owner, float strength, glm::vec3 color, float attenuation) :
	Component(owner),
	transform(owner->GetComponent<Transform>()),
	shaderData(LightData::CreatePoint(transform->GetPosition(), color, strength, attenuation))
{
	if (transform == nullptr)
	{
		throw std::runtime_error("PointLight construction failed: owning object does not have a Transform component");
	}
}

void PointLight::Use(unsigned int bufferID)
{
	shaderData.position = glm::vec4(transform->GetPosition(), 1.0f);

	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, LightData::UniformBlockSize, LightData::UniformBlockSize, &shaderData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
