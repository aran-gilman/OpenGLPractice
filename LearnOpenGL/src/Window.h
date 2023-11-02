#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <string>

class GLFWwindow;
class Window;

class IWindowListener
{
public:
	virtual ~IWindowListener() {}
	virtual void OnUpdate(Window* window, double elapsedTime) = 0;
	virtual void OnResize(int width, int height) = 0;
	virtual void OnKeyInput(int keyToken, int scancode, int action, int mods) = 0;
	virtual void OnMousePosition(double x, double y, double xOffset, double yOffset) = 0;
};

class Window
{
public:

	Window(int width, int height, const std::string& title);
	~Window();

	void Run(IWindowListener* windowListener);
	void Close();

	enum class CursorMode
	{
		Locked,
		Hidden,
		Normal,
	};
	void SetCursorMode(CursorMode mode);

private:
	GLFWwindow* window;
	IWindowListener* listener;

	double previousCursorX;
	double previousCursorY;
};

#endif
