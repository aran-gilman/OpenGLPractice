#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : matrix(1.0f)
{
	Set(position, rotation, scale);
}

float* Transform::GetMatrixPtr()
{
	return glm::value_ptr(matrix);
}

void Transform::Set(glm::vec3 newPosition, glm::vec3 newRotation, glm::vec3 newScale)
{
	position = newPosition;
	rotation = newRotation;
	scale = newScale;

	matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::scale(matrix, scale);
}
