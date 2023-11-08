#ifndef CAMERA_DATA_H
#define CAMERA_DATA_H

#include <glm/glm.hpp>

struct CameraData
{
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec3 position;
};

#endif

