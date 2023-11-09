#include "WorldSettings.h"

#include <GL/glew.h>

WorldSettings::WorldSettings(Object* owner, Color color) :
	Component(owner),
	color{ color.r, color.g, color.b, 1.0f }
{
}

void WorldSettings::Use(unsigned int bufferID) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, 16, &color);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
