#include "Game.h"

#include <cmath>
#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"

namespace {
	
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

}

// Not a permanent solution, but keeps more things out of the header file.
struct GameData
{
	Material material;
	Mesh mesh;
	Camera camera;

	std::vector<Transform> meshTransforms;
};

Game::Game() :
	window(800, 600, "OpenGL Tutorial")
{
	gameData = std::unique_ptr<GameData>(new GameData{
		Material(std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource), std::make_shared<Texture>("resources/Ground_02.png")),
		Mesh::MakeCube(),
		Camera(glm::vec3(0.0f, -1.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), 800, 600),
		std::vector<Transform>(10)
		});

	for (Transform& transform : gameData->meshTransforms)
	{
		glm::vec3 position = glm::sphericalRand(glm::linearRand(0.0f, 10.f));
		transform.Set(
			position,
			glm::vec3(glm::linearRand(0.0f, 180.0f), glm::linearRand(0.0f, 180.0f), glm::linearRand(0.0f, 180.0f)),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
	}

	window.SetCursorMode(Window::CursorMode::Locked);
}

Game::~Game()
{
}

void Game::OnUpdate(Window* window, double elapsedTime)
{
	gameData->camera.OnUpdate(elapsedTime);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gameData->material.Use();
	gameData->camera.Use(&gameData->material);
	for (const Transform& transform : gameData->meshTransforms)
	{
		gameData->material.GetShader()->Set4("transform", transform.GetMatrixPtr());
		gameData->mesh.Draw();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::OnResize(int width, int height)
{
	gameData->camera.OnResize(width, height);
}

void Game::OnKeyInput(int keyToken, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && keyToken == GLFW_KEY_ESCAPE)
	{
		window.Close();
	}
	else
	{
		gameData->camera.OnKeyInput(keyToken, scancode, action, mods);
	}
}

void Game::OnMousePosition(double x, double y, double xOffset, double yOffset)
{
	gameData->camera.OnCursorMove(xOffset, yOffset);
}

void Game::Run()
{
	window.Run(this);
}
