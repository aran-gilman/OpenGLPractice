#ifndef LIGHT_DATA_H
#define LIGHT_DATA_H

#include <glm/glm.hpp>

struct LightData
{
	static const int UniformBlockSize = 64;

	static LightData CreateDirectional(glm::vec3 direction, glm::vec3 color, float intensity)
	{
		return LightData{ glm::vec4(direction, 0.0f), glm::vec4(color, intensity), glm::vec4(color, intensity / 2), 0.0f };
	}

	static LightData CreatePoint(glm::vec3 position, glm::vec3 color, float intensity, float attenuation)
	{
		return LightData{ glm::vec4(position, 1.0f), glm::vec4(color, intensity), glm::vec4(color, intensity / 2), attenuation };
	}

	glm::vec4 position;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float attenuation;
};

#endif