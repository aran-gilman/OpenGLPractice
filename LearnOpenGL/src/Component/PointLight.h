#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glm/glm.hpp>

#include "../Color.h"
#include "Component.h"

class Transform;
class Object;

class PointLight : public Component
{
public:
	PointLight(Object* owner, float strength, Color color, float attenuation);

	void Use(unsigned int bufferID);

private:
	float strength;
	Color color;
	float attenuation;

	Transform* transform;
};

#endif

