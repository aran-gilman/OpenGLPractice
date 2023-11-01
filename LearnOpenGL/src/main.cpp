#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
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
		meshTransforms(std::vector<Transform>(10)),
		cameraTransform(glm::vec3(0.0f, -1.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
		projection(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)),
		cameraHeading(glm::vec3(0.0f, 0.0f, 0.0f))
	{
		for (Transform& transform : meshTransforms)
		{
			glm::vec3 position = glm::sphericalRand(glm::linearRand(0.0f, 10.f));
			transform.Set(
				position,
				glm::vec3(glm::linearRand(0.0f, 180.0f), glm::linearRand(0.0f, 180.0f), glm::linearRand(0.0f, 180.0f)),
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
		}
	}

	void OnUpdate(Window* window, double elapsedTime) override
	{
		cameraTransform.Translate(cameraHeading * 3.5f * (float)elapsedTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		material.Use();
		material.GetShader()->Set4("view", cameraTransform.GetMatrixPtr());
		material.GetShader()->Set4("projection", glm::value_ptr(projection));
		for (const Transform& transform : meshTransforms)
		{
			material.GetShader()->Set4("transform", transform.GetMatrixPtr());
			mesh.Draw();
		}
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

			if (keyToken == GLFW_KEY_A || keyToken == GLFW_KEY_LEFT)
			{
				cameraHeading.x += 1.0f;
			}

			if (keyToken == GLFW_KEY_D || keyToken == GLFW_KEY_RIGHT)
			{
				cameraHeading.x -= 1.0f;
			}

			if (keyToken == GLFW_KEY_S || keyToken == GLFW_KEY_DOWN)
			{
				cameraHeading.z -= 1.0f;
			}

			if (keyToken == GLFW_KEY_W || keyToken == GLFW_KEY_UP)
			{
				cameraHeading.z += 1.0f;
			}
		}

		if (action == GLFW_RELEASE)
		{
			if (keyToken == GLFW_KEY_A || keyToken == GLFW_KEY_LEFT)
			{
				cameraHeading.x -= 1.0f;
			}

			if (keyToken == GLFW_KEY_D || keyToken == GLFW_KEY_RIGHT)
			{
				cameraHeading.x += 1.0f;
			}

			if (keyToken == GLFW_KEY_S || keyToken == GLFW_KEY_DOWN)
			{
				cameraHeading.z += 1.0f;
			}

			if (keyToken == GLFW_KEY_W || keyToken == GLFW_KEY_UP)
			{
				cameraHeading.z -= 1.0f;
			}
		}
	}

	void OnMousePosition(double x, double y)
	{
	}

	void Run()
	{
		window.Run(this);
	}

private:
	Window window;

	Material material;
	Mesh mesh;

	std::vector<Transform> meshTransforms;
	Transform cameraTransform;
	glm::vec3 cameraHeading;

	glm::mat4 projection;
};

int main()
{
	Game().Run();
	return 0;
}