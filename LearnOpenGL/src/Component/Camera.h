#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "../ShaderInterface/CameraData.h"
#include "Component.h"

class Game;
class Material;
class Object;

class Camera : public Component
{
public:
	Camera(Object* owner, glm::vec3 position, glm::vec3 front, float width, float height);
	~Camera() override;

	void Use(unsigned int bufferID) const;
	void Clear() const;

private:
	CameraData shaderData;

	glm::vec3 heading;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	int width;
	int height;

	float mouseSensitivity;
	float pitch;
	float yaw;

	void HandleUpdate(double elapsedTime);
	void HandleKeyInput(int keyToken, int scancode, int action, int mods);
	void HandleResize(int width, int height);
	void HandleCursorMove(double xPos, double yPos, double xOffset, double yOffset);
};

#endif