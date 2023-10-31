#include "Window.h"

#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace
{
	// TODO: Figure out a good way to abstract this
	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}
}

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

	double previousTime = glfwGetTime();
	double currentTime = previousTime;
	while (!glfwWindowShouldClose(window))
	{
		previousTime = currentTime;
		currentTime = glfwGetTime();
		processInput(window);
		this->listener->OnUpdate(this, currentTime - previousTime);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}
