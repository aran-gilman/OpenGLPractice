#include <cmath>
#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

const char* vertexShaderSource = R"shader(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    vertexColor = aColor;
    texCoord = aTexCoord;
})shader";

const char* fragmentShaderSource = R"shader(
#version 330 core
in vec3 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D inTexture;

void main()
{
    FragColor = texture(inTexture, texCoord) * vec4(vertexColor, 1.0);
})shader";

int main()
{
	Window window(800, 600, "OpenGL Tutorial");
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource);
	std::shared_ptr<Texture> texture = std::make_shared<Texture>("resources/Ground_02.png");

	Material material(shader, texture);

	// Rectangle + triangle #1
	std::vector<float> vertices = {
		// positions        // colors          // texture coords
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

		 0.5f,  0.5f, 1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f, 1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, 1.0f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f
	};
	std::vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3,
		4, 5, 0,
		5, 1, 0,
		3, 2, 7,
		2, 6, 7,
		7, 6, 4,
		6, 5, 4,
	};
	Mesh mesh(vertices, indices);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));

	window.Run([&] (Window* window)
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			material.Use();
			material.GetShader()->Set4("transform", glm::value_ptr(transform));
			mesh.Use();
			glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	);

	return 0;
}