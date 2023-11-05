#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Event.h"
#include "Transform.h"

class Game;
class Material;

class Camera
{
public:
	Camera(Game* game, glm::vec3 position, glm::vec3 front, float width, float height);

	void Use() const;
	void Clear() const;

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

	unsigned int uboId;

	void HandleUpdate(double elapsedTime);
	void HandleKeyInput(int keyToken, int scancode, int action, int mods);
	void HandleResize(int width, int height);
	void HandleCursorMove(double xPos, double yPos, double xOffset, double yOffset);
};

#endif