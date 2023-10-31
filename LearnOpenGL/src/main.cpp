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
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0f);
    texCoord = aTexCoord;
})shader";

const char* fragmentShaderSource = R"shader(
#version 330 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D inTexture;

void main()
{
    FragColor = texture(inTexture, texCoord);
})shader";

class Game : IWindowListener
{
public:
	Game() :
		window(800, 600, "OpenGL Tutorial"),
		material(std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource), std::make_shared<Texture>("resources/Ground_02.png")),
		mesh(Mesh::MakeCube()),
		transform(glm::mat4(1.0f)),
		view(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, -10.0f))),
		projection(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)),
		rotation(0.0f)
	{
	}

	void OnUpdate(Window* window, double elapsedTime) override
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		rotation += glm::radians(45.0f * (float)elapsedTime);
		transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 1.0f, 0.0f));

		material.Use();
		material.GetShader()->Set4("transform", glm::value_ptr(transform));
		material.GetShader()->Set4("view", glm::value_ptr(view));
		material.GetShader()->Set4("projection", glm::value_ptr(projection));
		mesh.Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OnResize(int width, int height) override
	{
		glViewport(0, 0, width, height);
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	}

	void OnKeyInput(int keyToken, int scancode, int action, int mods) override
	{
		if (action == GLFW_PRESS)
		{
			if (keyToken == GLFW_KEY_ESCAPE)
			{
				window.Close();
			}
		}
	}

	void Run()
	{
		window.Run(this);
	}

private:
	Window window;

	Material material;
	Mesh mesh;

	glm::mat4 transform;
	glm::mat4 view;
	glm::mat4 projection;

	float rotation;
};

int main()
{
	Game().Run();
	return 0;
}