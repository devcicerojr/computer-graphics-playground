#include "WindowHandler.hpp"

using std::cout;
using std::endl;

namespace cgraph {

	WindowHandler::WindowHandler() :
	width_{800},
	height_{600},
	keys_state_{0},
	last_x_{0},
	last_y_{0},
	x_change_{0},
	y_change_{0},
	mouse_first_move_{true} {
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

	bool* WindowHandler::getKeysState() const {
		return keys_state_;
	}

	GLfloat WindowHandler::getXChange() {
		GLfloat x_amount = x_change_;
		x_change_ = 0.0f;
		return x_amount;
	}

	GLfloat WindowHandler::getYChange() {
		GLfloat y_amount = y_change_;
		y_change_ = 0.0f;
		return y_amount;
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

	// Handle keys and mouse input
		createCallbacks();

	// Locks cursor to the window and makes it invisible
		//glfwSetInputMode(main_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

		glfwSetWindowUserPointer(main_window_, this);
	}

	void WindowHandler::createCallbacks() {
		glfwSetKeyCallback(main_window_, onKeyEvent);
		glfwSetCursorPosCallback(main_window_, onCursorMoveEvent);
	}

	void WindowHandler::onKeyEvent(GLFWwindow* window, int key, int code, int action, int mode) {
		WindowHandler* the_window = static_cast<WindowHandler*>(glfwGetWindowUserPointer(window));
		if (!the_window) {
			cout << "Dynamic cast to WindowHandler failed!" << endl;
		}

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (key >= 0  && key < 1024) {
			if (action == GLFW_PRESS) {
				the_window->keys_state_[key] = true;
			}
			else if (action == GLFW_RELEASE) {
				the_window->keys_state_[key] = false;
			}
		}
	}

	void WindowHandler::onCursorMoveEvent(GLFWwindow* window, double xPos, double yPos) {
		WindowHandler* the_window = static_cast<WindowHandler*>(glfwGetWindowUserPointer(window));

		if (the_window->mouse_first_move_) {
			the_window->last_x_ = static_cast<GLfloat>(xPos);
			the_window->last_y_ = static_cast<GLfloat>(yPos);
			the_window->mouse_first_move_ = false;
		}

		the_window->x_change_ = static_cast<GLfloat>(xPos) - the_window->last_x_;
		the_window->y_change_ = the_window->last_y_ - static_cast<GLfloat>(yPos);

		the_window->last_x_ = static_cast<GLfloat>(xPos);
		the_window->last_y_ = static_cast<GLfloat>(yPos);
	}

} // end of namespace cgraph