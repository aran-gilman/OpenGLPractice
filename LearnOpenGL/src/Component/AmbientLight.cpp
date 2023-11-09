#include "AmbientLight.h"

#include <GL/glew.h>

AmbientLight::AmbientLight(Object* owner, Color color) :
	Component(owner),
	color{ color.r, color.g, color.b, 1.0f }
{
}

void AmbientLight::Use(unsigned int bufferID) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 16, &color);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
