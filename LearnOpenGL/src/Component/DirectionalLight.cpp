#include "DirectionalLight.h"

#include <GL/glew.h>

DirectionalLight::DirectionalLight(Object* owner, float strength, glm::vec3 color, glm::vec3 direction) :
	Component(owner),
	shaderData(LightData::CreateDirectional(direction, color, strength))
{
}

void DirectionalLight::Use(unsigned int bufferID) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, LightData::UniformBlockSize, &shaderData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
