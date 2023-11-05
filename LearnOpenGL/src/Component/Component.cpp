#include "Component.h"

Component::~Component()
{
}

Component::Component(Object* owner) : owner(owner)
{
}
