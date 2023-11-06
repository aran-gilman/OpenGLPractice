#include "ShaderBufferManager.h"

#include <cstddef>

#include <GL/glew.h>

ShaderBufferManager::ShaderBufferManager(std::string name, unsigned int bindingPoint, unsigned int size) :
	name(std::move(name)),
	bindingPoint(bindingPoint)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_UNIFORM_BUFFER, ID);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ID);
}

ShaderBufferManager::~ShaderBufferManager()
{
	glDeleteBuffers(1, &ID);
}