#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>

#include "Component.h"

class Object
{
public:
	Object() {}

	template <class TComponent, class... Args>
	void AddComponent(Args&&... args)
	{
		components.push_back(std::make_unique<TComponent>(this, std::forward<Args>(args)...));
	}

	template <class TComponent>
	TComponent* GetComponent()
	{
		for (const auto& ptr : components)
		{
			TComponent* component = dynamic_cast<TComponent*>(ptr.get());
			if (component != nullptr)
			{
				return component;
			}
		}
		return nullptr;
	}

	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

private:
	std::vector<std::unique_ptr<Component>> components;
};

#endif
