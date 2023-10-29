#include "Window.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace
{
	void onFramebufferSizeChange(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

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
		std::cout << "ERROR: Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, onFramebufferSizeChange);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "ERROR: Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
	}
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Run(std::function<void(Window*)> render)
{
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		render(this);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}
