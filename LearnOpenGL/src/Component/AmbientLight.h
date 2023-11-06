#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "../Color.h"
#include "Component.h"

class Object;

class AmbientLight : public Component
{
public:
	AmbientLight(Object* owner, float strength, Color color);
	~AmbientLight() override;

	void Use();

private:
	float strength;
	Color color;

	unsigned int uboID;
};

#endif

