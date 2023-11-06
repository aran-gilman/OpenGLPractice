#include "AmbientLight.h"

#include <cstddef>

#include <GL/glew.h>

AmbientLight::AmbientLight(Object* owner, float strength, Color color) :
	Component(owner),
	strength(strength),
	color(color)
{
}

void AmbientLight::Use(unsigned int bufferID) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 3 * sizeof(float), &color);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
