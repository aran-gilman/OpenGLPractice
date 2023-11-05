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

#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "Shader.h"
#include "Texture.h"

#include "Component/Camera.h"
#include "Component/MeshRenderer.h"
#include "Component/Transform.h"

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

Game::Game() :
	window(800, 600, "OpenGL Tutorial")
{
	std::shared_ptr<Shader> defaultShader = std::make_shared<Shader>(ReadFile("resources/shaders/standardLit.vert"), ReadFile("resources/shaders/standard.frag"));

	std::shared_ptr<Material> cubeMaterial = std::make_shared<Material>(defaultShader, std::make_shared<Texture>("resources/Ground_02.png"));
	std::shared_ptr<Material> lightSourceMaterial = std::make_shared<Material>(defaultShader, nullptr);

	std::shared_ptr<Mesh> cubeMesh(Mesh::MakeCube());

	for (int i = 0; i < 10; i++)
	{
		Object* object = CreateObject();
		glm::vec3 position = glm::sphericalRand(glm::linearRand(0.0f, 10.f));
		object->AddComponent<Transform>(
			position,
			glm::vec3(glm::linearRand(0.0f, 180.0f), glm::linearRand(0.0f, 180.0f), glm::linearRand(0.0f, 180.0f)),
			glm::vec3(1.0f, 1.0f, 1.0f)
		);
		object->AddComponent<MeshRenderer>(cubeMesh, cubeMaterial);
	}

	Object* lightSourceObject = CreateObject();
	lightSourceObject->AddComponent<Transform>();
	lightSourceObject->AddComponent<MeshRenderer>(cubeMesh, lightSourceMaterial);

	Object* cameraObject = CreateObject();
	cameraObject->AddComponent<Camera>(glm::vec3(0.0f, -1.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), 800, 600);

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

Object* Game::CreateObject()
{
	objects.push_back(std::make_unique<Object>(this));
	return objects.back().get();
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
	}
}

void Game::HandleKeyInput(int keyToken, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && keyToken == GLFW_KEY_ESCAPE)
	{
		window.Close();
	}
}
