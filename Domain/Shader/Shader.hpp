#pragma once

#include <string>
#include <fstream>

#include <GL/glew.h>


namespace cgraph {
	class Shader {
	private:
		GLuint id_, uniform_projection_, uniform_model_;

		void compile(const char* vertex_code, const char* fragment_code);
		void add(GLuint the_program, const char* shader_code, GLenum shader_type);
	public:
		Shader();
		void createFromString(const char* vertex_code, const char* fragment_code);
		GLuint getProjectionLocation() const;
		GLuint getModelLocation() const;
		void use() const;
		void clear();
		~Shader();
	};
} // end namespace cgraph
