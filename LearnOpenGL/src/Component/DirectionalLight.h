#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <glm/glm.hpp>

#include "../Color.h"
#include "../ShaderInterface/LightData.h"

#include "Component.h"

class Object;

class DirectionalLight : public Component
{
public:
	DirectionalLight(Object* owner, float strength, glm::vec3 color, glm::vec3 direction);

	void Use(unsigned int bufferID) const;

private:
	LightData shaderData;
};

#endif

