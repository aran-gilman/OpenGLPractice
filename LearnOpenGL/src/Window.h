#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <optional>
#include <string>

class GLFWwindow;
class Window;

struct WindowCallbacks
{
	std::optional<std::function<void(Window*, double)>> OnRender;
	std::optional<std::function<void(int width, int height)>> OnResize;
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
	std::function<void(int, int)> resizeCallback;

	void OnResize(int width, int height);
};

#endif
