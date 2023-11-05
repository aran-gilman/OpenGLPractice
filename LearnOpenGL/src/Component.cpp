#include "Component.h"

#include <memory>

#include "Object.h"

Component::~Component()
{
}

Component::Component(Object* owner) : owner(owner)
{
}
