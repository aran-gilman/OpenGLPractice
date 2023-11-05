#ifndef COMPONENT_H
#define COMPONENT_H

class Object;

class Component
{
public:
	virtual ~Component();

	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

protected:
	Component(Object* owner);

private:
	Object* owner;
};

#endif
