#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <optional>
#include <string>

class GLFWwindow;
class Window;

struct WindowCallbacks
{
	std::function<void(Window*, double)> OnRender;
	std::function<void(int width, int height)> OnResize;

	WindowCallbacks();
};

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	void Run(WindowCallbacks callbacks);
	void Close();

private:
	GLFWwindow* window;
	WindowCallbacks callbacks;

	void OnResize(int width, int height);
};

#endif
