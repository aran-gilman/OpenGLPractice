#include "Window.h"

#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Window::Window(int width, int height, const std::string& title)
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

void Window::Run()
{
	glfwSetFramebufferSizeCallback(window,
		[](GLFWwindow* window, int width, int height)
		{
			Window* user = static_cast<Window*>(glfwGetWindowUserPointer(window));
			user->OnResize().Invoke(width, height);
		});
	glfwSetKeyCallback(window,
		[](GLFWwindow* window, int keyToken, int scancode, int action, int mods)
		{
			Window* user = static_cast<Window*>(glfwGetWindowUserPointer(window));
			user->OnKeyInput().Invoke(keyToken, scancode, action, mods);
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
			user->OnMousePosition().Invoke(x, y, xOffset, yOffset);
		});

	double previousTime = glfwGetTime();
	double currentTime = previousTime;
	while (!glfwWindowShouldClose(window))
	{
		previousTime = currentTime;
		currentTime = glfwGetTime();
		this->OnUpdate().Invoke(currentTime - previousTime);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}

void Window::SetCursorMode(CursorMode mode)
{
	switch (mode)
	{
	case Window::CursorMode::Locked:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	case Window::CursorMode::Hidden:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case Window::CursorMode::Normal:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	default:
		break;
	}
}
