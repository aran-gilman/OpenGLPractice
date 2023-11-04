#include "Shader.h"

#include <iostream>

#include <GL/glew.h>

Shader::Shader(std::string_view vertexShaderCode, std::string_view fragmentShaderCode)
{
	int success;
	char infoLog[512];

	const char* vertexShader = vertexShaderCode.data();
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShader, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "Vertex shader compilation failed! " << infoLog << std::endl;
	}

	const char* fragmentShader = fragmentShaderCode.data();
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShader, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "Fragment shader compilation failed! " << infoLog << std::endl;
	}

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cerr << "Shader program linking failed! " << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::Use()
{
	glUseProgram(id);
}

void Shader::Set(std::string_view name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.data()), (int)value);
}

void Shader::Set(std::string_view name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.data()), value);
}

void Shader::Set(std::string_view name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.data()), value);
}

void Shader::Set(std::string_view name, float value0, float value1, float value2) const
{
	glUniform3f(glGetUniformLocation(id, name.data()), value0, value1, value2);
}

void Shader::Set(std::string_view name, float value0, float value1, float value2, float value3) const
{
	glUniform4f(glGetUniformLocation(id, name.data()), value0, value1, value2, value3);
}

void Shader::Set4(std::string_view name, const float* value)
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.data()), 1, GL_FALSE, value);
}
