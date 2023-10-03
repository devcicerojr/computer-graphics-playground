#include "WindowHandler.hpp"

using std::cout;
using std::endl;

namespace cgraph {

	WindowHandler::WindowHandler() {
		width_ = 800;
		height_ = 600;
	}

	WindowHandler::WindowHandler(GLint window_width, GLint window_height) {
		width_ = window_width;
		height_ = window_height;
	}

	WindowHandler::~WindowHandler() {
		glfwDestroyWindow(main_window_);
		glfwTerminate();
	}

	GLint WindowHandler::getBufferWidth() const {
		return buffer_width_;
	}

	GLint WindowHandler::getBufferHeight() const {
		return buffer_height_;
	}

	bool WindowHandler::getShouldClose() const {
		return glfwWindowShouldClose(main_window_);
	}

	void WindowHandler::swapBuffers() {
		glfwSwapBuffers(main_window_); 
	}

	int WindowHandler::initialize() {
		// Initialize GLFW
		if (!glfwInit()) {
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

		main_window_ = glfwCreateWindow(width_, height_, "Test Window", NULL, NULL);

		if (!main_window_) {
			cout << "GLFW window creation failed" << endl;
			glfwTerminate();
			return 1;
		}

	// Get Buffer Size Information
		glfwGetFramebufferSize(main_window_, &buffer_width_, &buffer_height_);

	// set context for GLEW to use
		glfwMakeContextCurrent(main_window_);

	// Allow modern extension features
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK) {
			cout << "GLEW initialization failed!" << endl;
			glfwDestroyWindow(main_window_);
			glfwTerminate();
			return 1;
		}

		glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
		glViewport(0, 0, buffer_width_, buffer_height_);
	}

} // end of namespace cgraph