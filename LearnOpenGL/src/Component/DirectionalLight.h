#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <glm/glm.hpp>

#include "../Color.h"
#include "Component.h"

class Object;

class DirectionalLight : public Component
{
public:
	DirectionalLight(Object* owner, float strength, Color color, glm::vec3 direction);

	void Use(unsigned int bufferID) const;

private:
	float strength;
	Color color;
	glm::vec4 inverseDirection;
};

#endif

