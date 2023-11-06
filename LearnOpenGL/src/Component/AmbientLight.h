#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "../Color.h"
#include "Component.h"

class Object;

class AmbientLight : public Component
{
public:
	AmbientLight(Object* owner, float strength, Color color);

	void Use(unsigned int bufferID) const;

private:
	float strength;
	Color color;
};

#endif

