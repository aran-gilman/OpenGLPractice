#include "Camera.h"

#include "Material.h"
#include "Shader.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, float width, float height) :
	transform(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
	front(front),
	projection(glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f)),
	heading(glm::vec3(0.0f, 0.0f, 0.0f)),
	width(width),
	height(height)
{
}

void Camera::OnUpdate(double elapsedTime)
{
	transform.Translate(heading * 3.5f * (float)elapsedTime);
}

void Camera::OnKeyInput(int keyToken, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (keyToken == GLFW_KEY_A || keyToken == GLFW_KEY_LEFT)
		{
			heading.x += 1.0f;
		}

		if (keyToken == GLFW_KEY_D || keyToken == GLFW_KEY_RIGHT)
		{
			heading.x -= 1.0f;
		}

		if (keyToken == GLFW_KEY_S || keyToken == GLFW_KEY_DOWN)
		{
			heading.z -= 1.0f;
		}

		if (keyToken == GLFW_KEY_W || keyToken == GLFW_KEY_UP)
		{
			heading.z += 1.0f;
		}
	}

	if (action == GLFW_RELEASE)
	{
		if (keyToken == GLFW_KEY_A || keyToken == GLFW_KEY_LEFT)
		{
			heading.x -= 1.0f;
		}

		if (keyToken == GLFW_KEY_D || keyToken == GLFW_KEY_RIGHT)
		{
			heading.x += 1.0f;
		}

		if (keyToken == GLFW_KEY_S || keyToken == GLFW_KEY_DOWN)
		{
			heading.z += 1.0f;
		}

		if (keyToken == GLFW_KEY_W || keyToken == GLFW_KEY_UP)
		{
			heading.z -= 1.0f;
		}
	}
}

void Camera::OnResize(int width, int height)
{
	projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	this->width = width;
	this->height = height;
}

void Camera::Use(Material* material)
{
	glViewport(0, 0, width, height);
	material->GetShader()->Set4("view", transform.GetMatrixPtr());
	material->GetShader()->Set4("projection", glm::value_ptr(projection));
}
