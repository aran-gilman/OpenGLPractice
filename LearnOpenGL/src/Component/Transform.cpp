#include "Transform.h"

#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

Transform::Transform(Object* owner, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Component(owner), matrix(1.0f)
{
	Set(position, rotation, scale);
}

const float* Transform::GetMatrixPtr() const
{
	return glm::value_ptr(matrix);
}

const float* Transform::GetNormalMatrixPtr() const
{
	return glm::value_ptr(normalMatrix);
}

void Transform::Set(glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale)
{
	position = newPosition;
	rotation = newRotation;
	scale = newScale;

	matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::scale(matrix, scale);

	normalMatrix = glm::mat3(glm::transpose(glm::inverse(matrix)));
}

void Transform::LookAt(glm::vec3 otherPosition)
{
	matrix = glm::lookAt(position, otherPosition, glm::vec3(0.0f, 1.0f, 0.0f));

	float x, y, z;
	glm::extractEulerAngleXYX(matrix, x, y, z);
	rotation = glm::vec3(x, y, z);

	matrix = glm::scale(matrix, scale);
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(matrix)));
}

void Transform::LookAt(glm::vec3 otherPosition, glm::vec3 newPosition)
{
	position = newPosition;
	LookAt(otherPosition);
}
