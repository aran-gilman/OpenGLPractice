#ifndef CAMERA_DATA_H
#define CAMERA_DATA_H

#include <glm/glm.hpp>

struct CameraData
{
	static const int UniformBlockSize = 144;

	glm::mat4 view;
	glm::mat4 projection;
	glm::vec4 position;
};

#endif

