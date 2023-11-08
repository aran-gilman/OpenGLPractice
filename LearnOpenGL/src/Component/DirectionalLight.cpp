#include "DirectionalLight.h"

#include <GL/glew.h>

DirectionalLight::DirectionalLight(Object* owner, float strength, Color color, glm::vec3 direction) :
	Component(owner),
	strength(strength),
	color(color),
	inverseDirection(-direction)
{
}

void DirectionalLight::Use(unsigned int bufferID) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 3 * sizeof(float), &color);
	glBufferSubData(GL_UNIFORM_BUFFER, 32, 3 * sizeof(float), &inverseDirection);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
