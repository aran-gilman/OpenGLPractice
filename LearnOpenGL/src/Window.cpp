#include "Window.h"

#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Window::Window(int width, int height, const std::string& title) : listener(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwSetWindowUserPointer(window, this);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, width, height);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLEW");
	}

	glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Run(IWindowListener* listener)
{
	if (listener == nullptr)
	{
		throw std::invalid_argument("listener must be non-null");
	}

	this->listener = listener;
	glfwSetFramebufferSizeCallback(window,
		[](GLFWwindow* window, int width, int height)
		{
			Window* user = static_cast<Window*>(glfwGetWindowUserPointer(window));
			user->listener->OnResize(width, height);
		});
	glfwSetKeyCallback(window,
		[](GLFWwindow* window, int keyToken, int scancode, int action, int mods)
		{
			Window* user = static_cast<Window*>(glfwGetWindowUserPointer(window));
			user->listener->OnKeyInput(keyToken, scancode, action, mods);
		});

	glfwGetCursorPos(window, &previousCursorX, &previousCursorY);
	glfwSetCursorPosCallback(window,
		[](GLFWwindow* window, double x, double y)
		{
			Window* user = static_cast<Window*>(glfwGetWindowUserPointer(window));
			double xOffset = x - user->previousCursorX;
			double yOffset = y - user->previousCursorY;
			user->previousCursorX = x;
			user->previousCursorY = y;
			user->listener->OnMousePosition(x, y, xOffset, yOffset);
		});

	double previousTime = glfwGetTime();
	double currentTime = previousTime;
	while (!glfwWindowShouldClose(window))
	{
		previousTime = currentTime;
		currentTime = glfwGetTime();
		this->listener->OnUpdate(this, currentTime - previousTime);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}
