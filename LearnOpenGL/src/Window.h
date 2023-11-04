#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <string>

#include "Event.h"

class GLFWwindow;

class Window
{
public:

	Window(int width, int height, const std::string& title);
	~Window();

	void Run();
	void Close();

	enum class CursorMode
	{
		Locked,
		Hidden,
		Normal,
	};
	void SetCursorMode(CursorMode mode);

	Event<const double&>& OnUpdate() { return onUpdate; }
	Event<int, int>& OnResize() { return onResize; }
	Event<int, int, int, int>& OnKeyInput() { return onKeyInput; }
	Event<double, double, double, double>& OnMousePosition() { return onMousePosition; }

private:
	GLFWwindow* window;

	double previousCursorX;
	double previousCursorY;

	Event<const double&> onUpdate;
	Event<int, int> onResize;
	Event<int, int, int, int> onKeyInput;
	Event<double, double, double, double> onMousePosition;
};

#endif
