#include <cmath>
#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

const char* vertexShaderSource = R"shader(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 texCoord;

uniform vec3 offset;

void main()
{
    gl_Position = vec4(aPos, 1.0) + vec4(offset, 1.0);
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

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

void onFramebufferSizeChange(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "ERROR: Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, onFramebufferSizeChange);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "ERROR: Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
	}

	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource);
	std::shared_ptr<Texture> texture = std::make_shared<Texture>("resources/Ground_02.png");

	Material material(shader, texture);

	// Rectangle + triangle #1
	std::vector<float> vertices = {
		// positions        // colors          // texture coords
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f
	};
	std::vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3
	};
	Mesh mesh(vertices, indices);

	Vector3 position(0, 0, 0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		position.y = sin(glfwGetTime());
		material.Use();
		material.GetShader()->Set("offset", position.x, position.y, position.z);
		mesh.Use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}