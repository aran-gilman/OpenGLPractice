#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Event.h"
#include "Transform.h"

class Material;

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 front, float width, float height);

	void OnUpdate(double elapsedTime);
	void OnKeyInput(int keyToken, int scancode, int action, int mods);
	void OnResize(int width, int height);
	void OnCursorMove(double xPos, double yPos, double xOffset, double yOffset);

	void Use(Material* material);

private:
	glm::vec3 position;
	glm::vec3 heading;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	glm::mat4 view;
	glm::mat4 projection;

	int width;
	int height;

	float mouseSensitivity;
	float pitch;
	float yaw;
};

#endif