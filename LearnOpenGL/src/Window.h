#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <string>

class GLFWwindow;

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	void Run(std::function<void(Window*)> render);
	void Close();

private:
	GLFWwindow* window;
};

#endif
