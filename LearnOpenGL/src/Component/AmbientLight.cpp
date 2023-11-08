#include "AmbientLight.h"

#include <GL/glew.h>

AmbientLight::AmbientLight(Object* owner, float strength, Color color) :
	Component(owner),
	strength(strength),
	color{ color.r, color.g, color.b, 1.0f }
{
}

void AmbientLight::Use(unsigned int bufferID) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 4 * sizeof(float), &color);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
