#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glm/glm.hpp>

#include "../Color.h"
#include "../ShaderInterface/LightData.h"

#include "Component.h"

class Transform;
class Object;

class PointLight : public Component
{
public:
	PointLight(Object* owner, float strength, glm::vec3 color, float attenuation);

	void Use(unsigned int bufferID);

private:
	Transform* transform;
	LightData shaderData;
};

#endif

