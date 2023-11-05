#include "AmbientLight.h"

#include <cstddef>

#include <GL/glew.h>

namespace
{
	unsigned int CreateAmbientLightUniformBuffer()
	{
		unsigned int uboId = 0;
		glGenBuffers(1, &uboId);
		glBindBuffer(GL_UNIFORM_BUFFER, uboId);
		glBufferData(GL_UNIFORM_BUFFER, 32, NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboId);
		return uboId;
	}
}

AmbientLight::AmbientLight(float strength, Color color) :
	strength(strength),
	color(color),
	uboID(CreateAmbientLightUniformBuffer())
{
}

AmbientLight::~AmbientLight()
{
	glDeleteBuffers(1, &uboID);
}

void AmbientLight::Use()
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboID);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 3 * sizeof(float), &color);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
