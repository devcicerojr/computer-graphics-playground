#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace cgraph {
	class WindowHandler {
	private:
		GLFWwindow *main_window_;
		GLint width_, height_;
		GLint buffer_width_, buffer_height_;
	public:

		WindowHandler();
		WindowHandler(GLint window_width, GLint window_height);
		~WindowHandler();

		int initialize();
		GLint getBufferWidth() const;
		GLint getBufferHeight() const;
		bool getShouldClose() const;
		void swapBuffers();

	};
} // end namespace cgraph