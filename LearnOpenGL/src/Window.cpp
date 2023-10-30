#include "Window.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace
{
	// Because GLFW's framebuffer resizing uses a function pointer, we can't pass in a non-static member function or a capturing lambda.
	// So, if we want to wrap the callback and hide the use of GLFW from Window users, we have to use some sort of static state.
	static bool windowResized = false;

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
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int, int) { windowResized = true; });

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

void Window::Run(WindowCallbacks callbacks)
{
	std::function<void(Window*, double)> onRender = callbacks.OnRender.value_or([](Window*, double) {});
	std::function<void(int, int)> onResize = callbacks.OnResize.value_or([](int, int) {});

	double previousTime = glfwGetTime();
	double currentTime = previousTime;
	while (!glfwWindowShouldClose(window))
	{
		previousTime = currentTime;
		currentTime = glfwGetTime();
		if (windowResized)
		{
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			onResize(width, height);
			windowResized = false;
		}
		processInput(window);
		onRender(this, currentTime - previousTime);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}
