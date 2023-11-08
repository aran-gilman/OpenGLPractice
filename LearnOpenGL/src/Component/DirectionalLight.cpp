#include "DirectionalLight.h"

#include <GL/glew.h>

DirectionalLight::DirectionalLight(Object* owner, float strength, Color color, glm::vec3 direction) :
	Component(owner),
	strength(strength),
	color{ color.r, color.g, color.b, 1.0f },
	inverseDirection(-direction.x, -direction.y, -direction.z, 0.0f)
{
}

void DirectionalLight::Use(unsigned int bufferID) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 4 * sizeof(float), &color);
	glBufferSubData(GL_UNIFORM_BUFFER, 32, 4 * sizeof(float), &inverseDirection);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
