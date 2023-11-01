#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform
{
public:
	Transform() : Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)) {}
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetRotation() const { return rotation; }
	glm::vec3 GetScale() const { return scale; }

	glm::mat4 GetMatrix() const { return matrix; }
	const float* GetMatrixPtr() const;

	void Set(glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale);

	void SetPosition(glm::vec3 newPosition) { Set(newPosition, rotation, scale); }
	void SetRotation(glm::vec3 newRotation) { Set(position, newRotation, scale); }
	void SetScale(glm::vec3 newScale) { Set(position, rotation, newScale); }

	void LookAt(glm::vec3 otherPosition);
	void LookAt(glm::vec3 otherPosition, glm::vec3 newPosition);

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 matrix;
};

#endif