#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

using std::shared_ptr;

namespace cgraph {
	class WindowHandler {
	private:
		GLFWwindow* main_window_;
		GLint width_, height_;
		GLint buffer_width_, buffer_height_;
		mutable bool keys_state_[1024] = {0};
		GLfloat last_x_, last_y_, x_change_, y_change_;
		bool mouse_first_move_;

		void createCallbacks();
	public:

		WindowHandler();
		WindowHandler(GLint window_width, GLint window_height);
		~WindowHandler();

		int initialize();
		GLint getBufferWidth() const;
		GLint getBufferHeight() const;
		bool getShouldClose() const;
		void swapBuffers();

		bool * getKeysState() const;
		GLfloat getXChange();
		GLfloat getYChange();

		static void onKeyEvent(GLFWwindow* window, int key, int code, int action, int mode);
		static void onCursorMoveEvent(GLFWwindow* window, double xPos, double yPos);
	};
} // end namespace cgraph