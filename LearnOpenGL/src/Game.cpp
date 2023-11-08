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

#include "Color.h"
#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "Shader.h"
#include "Texture.h"

#include "Component/AmbientLight.h"
#include "Component/Camera.h"
#include "Component/DirectionalLight.h"
#include "Component/MeshRenderer.h"
#include "Component/PointLight.h"
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
	window(800, 600, "OpenGL Tutorial"),
	cameraBuffer("Camera", 0, 2 * sizeof(glm::mat4)),
	ambientLightBuffer("AmbientLight", 1, 32),
	directionalLightBuffer("DirectionalLight", 2, 48),
	pointLightBuffer("PointLight", 3, 64)
{
	std::vector<ShaderBufferManager*> uniformBlocks{ &cameraBuffer, &ambientLightBuffer, &directionalLightBuffer, &pointLightBuffer };

	std::shared_ptr<Shader> defaultShader = std::make_shared<Shader>(
		ReadFile("resources/shaders/standardUnlit.vert"),
		ReadFile("resources/shaders/standardLit.frag"),
		uniformBlocks);
	defaultShader->Set("color", 1.0f, 1.0f, 1.0f, 1.0f);

	std::shared_ptr<Material> cubeMaterial = std::make_shared<Material>(defaultShader, std::make_shared<Texture>("resources/Ground_02.png"));

	std::shared_ptr<Shader> texturelessShader = std::make_shared<Shader>(
		ReadFile("resources/shaders/standardUnlit.vert"),
		ReadFile("resources/shaders/texturelessUnlit.frag"),
		uniformBlocks);
	texturelessShader->Set("color", 0.0f, 0.9f, 1.0f, 1.0f);
	std::shared_ptr<Material> lightSourceMaterial = std::make_shared<Material>(texturelessShader, nullptr);

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
	lightSourceObject->AddComponent<Transform>(glm::vec3(5.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	lightSourceObject->AddComponent<MeshRenderer>(cubeMesh, lightSourceMaterial);
	lightSourceObject->AddComponent<PointLight>(0.5f, Color{ 0.0f, 0.9f, 1.0f }, 1.0f)->Use(pointLightBuffer.GetID());

	Object* cameraObject = CreateObject();
	cameraObject->AddComponent<Camera>(glm::vec3(0.0f, -1.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), 800, 600);

	Object* scene = CreateObject();
	scene->AddComponent<AmbientLight>(0.2f, Color{1.0f, 1.0f, 1.0f, 1.0f })->Use(ambientLightBuffer.GetID());
	scene->AddComponent<DirectionalLight>(1.0f, Color{ 1.0f, 1.0f, 1.0f, 1.0f }, glm::vec3(1.0f, 0.0f, 0.0f))->Use(directionalLightBuffer.GetID());

	window.OnUpdate().Register(std::bind_front(&Game::HandleUpdate, this));
	window.OnKeyInput().Register(std::bind_front(&Game::HandleKeyInput, this));

	window.SetCursorMode(Window::CursorMode::Locked);
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
		camera->Use(cameraBuffer.GetID());
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
