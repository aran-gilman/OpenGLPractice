#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <map>

using EventHandle = uint32_t;

template<class... TArgs>
class Event
{
public:
	Event() : nextHandle(0) {}

	void Invoke(TArgs... args)
	{
		for (const auto& [handle, callback] : callbacks)
		{
			callback(args...);
		}
	}

	EventHandle Register(std::function<void(TArgs...)> callback)
	{
		EventHandle handle = nextHandle;
		callbacks[handle] = callback;
		nextHandle++;
		return handle;
	}

	void Unregister(EventHandle handle)
	{
		callbacks.erase(handle);
	}

	Event(const Event&) = delete;
	Event& operator=(const Event&) = delete;

private:
	std::map<EventHandle, std::function<void(TArgs...)>> callbacks;
	EventHandle nextHandle;
};

#endif
