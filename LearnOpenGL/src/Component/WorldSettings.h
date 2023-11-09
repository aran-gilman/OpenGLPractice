#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "../Color.h"
#include "Component.h"

class Object;

class WorldSettings : public Component
{
public:
	WorldSettings(Object* owner, Color color);

	void Use(unsigned int bufferID) const;

private:
	Color color;
};

#endif

