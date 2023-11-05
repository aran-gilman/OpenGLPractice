#include "Game.h"

#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>

#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"

namespace {
	std::string ReadFile(std::string_view path)
	{
		std::ifstream fileStream;
		fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fileStream.open(path);
		std::stringstream stringStream;
		stringStream << fileStream.rdbuf();
		return stringStream.str();
	}
}

// Not a permanent solution, but keeps more things out of the header file.
struct GameData
{
	Material material;
	Mesh mesh;
};

Game::Game() :
	window(800, 600, "OpenGL Tutorial")
{
	gameData = std::unique_ptr<GameData>(new GameData{
		Material(std::make_shared<Shader>(ReadFile("resources/shaders/standardLit.vert"), ReadFile("resources/shaders/standard.frag")), std::make_shared<Texture>("resources/Ground_02.png")),
		Mesh::MakeCube()
		});

	for (int i = 0; i < 10; i++)
	{
		objects.push_back(std::make_unique<Object>(this));

		Object* object = objects.back().get();
		glm::vec3 position = glm::sphericalRand(glm::linearRand(0.0f, 10.f));
		object->AddComponent<Transform>(
			position,
			glm::vec3(glm::linearRand(0.0f, 180.0f), glm::linearRand(0.0f, 180.0f), glm::linearRand(0.0f, 180.0f)),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
	}

	{
		objects.push_back(std::make_unique<Object>(this));
		Object* cameraObject = objects.back().get();
		cameraObject->AddComponent<Camera>(glm::vec3(0.0f, -1.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), 800, 600);
	}

	window.SetCursorMode(Window::CursorMode::Locked);

	window.OnUpdate().Register(std::bind_front(&Game::HandleUpdate, this));
	window.OnKeyInput().Register(std::bind_front(&Game::HandleKeyInput, this));
}

Game::~Game()
{
}

void Game::Run()
{
	window.Run();
}

void Game::RegisterCamera(Camera* camera)
{
	cameras.push_back(camera);
}

void Game::UnregisterCamera(Camera* camera)
{
	std::erase(cameras, camera);
}

void Game::HandleUpdate(double elapsedTime)
{
	onUpdate.Invoke(elapsedTime);

	for (const auto& camera : cameras)
	{
		camera->Use();
		camera->Clear();
		onRender.Invoke(elapsedTime);

		gameData->material.Use();
		for (const auto& obj : objects)
		{
			Transform* transform = obj->GetComponent<Transform>();
			if (transform != nullptr)
			{
				gameData->material.GetShader()->Set4("transform", transform->GetMatrixPtr());
				gameData->mesh.Draw();
			}
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Game::HandleKeyInput(int keyToken, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && keyToken == GLFW_KEY_ESCAPE)
	{
		window.Close();
	}
}
