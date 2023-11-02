#include "Camera.h"

#include "Material.h"
#include "Shader.h"

namespace
{
	glm::mat4 CalculateViewMatrix(glm::vec3 position, glm::vec3 front, glm::vec3 up)
	{
		return glm::lookAt(position, position + front, up);
	}
}

Camera::Camera(glm::vec3 position, glm::vec3 front, float width, float height) :
	position(position),
	heading(glm::vec3(0.0f, 0.0f, 0.0f)),

	front(glm::normalize(front)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	right(glm::normalize(glm::cross(this->front, this->up))),

	view(glm::mat4(1.0f)),
	projection(glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f)),

	width(width),
	height(height),

	mouseSensitivity(0.1f),
	pitch(glm::degrees(std::asin(this->front.y))),
	yaw(glm::degrees(std::asin(this->front.z / std::cos(glm::radians(pitch)))))
{
	view = CalculateViewMatrix(position, front, up);
}

void Camera::OnUpdate(double elapsedTime)
{
	glm::vec3 rawMovement = heading.x * right - heading.z * front;
	rawMovement.y = 0;
	position += rawMovement * 3.5f * (float)elapsedTime;
	view = CalculateViewMatrix(position, front, up);
}

void Camera::OnKeyInput(int keyToken, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
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

	if (action == GLFW_RELEASE)
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
}

void Camera::OnResize(int width, int height)
{
	projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	this->width = width;
	this->height = height;
}

void Camera::OnCursorMove(double xOffset, double yOffset)
{
	yaw += (xOffset * mouseSensitivity);
	pitch += (-yOffset * mouseSensitivity);

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	front.y = std::sin(glm::radians(pitch));
	front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
	right = glm::normalize(glm::cross(front, up));
}

void Camera::Use(Material* material)
{
	glViewport(0, 0, width, height);
	material->GetShader()->Set4("view", glm::value_ptr(view));
	material->GetShader()->Set4("projection", glm::value_ptr(projection));
}
