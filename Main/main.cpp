#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

const GLint WIDTH = 800 , HEIGHT = 600;

int main() {
	// Initialize GLFW
	if(!glfwInit()) {
		cout << "Error when initializing glfw!" << endl;
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Window Properties
	// OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile = No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allows forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);

	if (!mainWindow) {
		cout << "GLFW window creation failed" << endl;
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size Information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		cout << "GLEW initialization failed!" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	while(!glfwWindowShouldClose(mainWindow)) {
		// Get and Handle User Input Events
		glfwPollEvents();

		// Clear window
		glClearColor(1.0f, 0.0f , 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mainWindow);
	}
	

	return 0;
}
