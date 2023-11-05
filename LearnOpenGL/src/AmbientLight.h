#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "Color.h"

class AmbientLight
{
public:
	AmbientLight(float strength, Color color);
	~AmbientLight();

	void Use();

private:
	float strength;
	Color color;

	unsigned int uboID;
};

#endif

