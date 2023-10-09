#pragma once

#include <string>
#include <fstream>

#include <GL/glew.h>

using std::string;


namespace cgraph {
	class Shader {
	private:
		GLuint id_, uniform_projection_, uniform_model_, uniform_view_;

		void compile(const char* vertex_code, const char* fragment_code);
		void add(GLuint the_program, const char* shader_code, GLenum shader_type);
	public:
		Shader();
		void createFromString(const char* vertex_code, const char* fragment_code);
		void createFromFile(const string& vertex_shader_path, const string& fragment_shader_path);
		
		string readFile(const string& file_path);

		GLuint getProjectionLocation() const;
		GLuint getModelLocation() const;
		GLuint getViewLocation() const;
		void use() const;
		void clear();
		~Shader();
	};
} // end namespace cgraph
