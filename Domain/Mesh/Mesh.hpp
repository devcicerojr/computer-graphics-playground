#pragma once

#include <GL/glew.h>

namespace cgraph {
	class Mesh {
	private:
		GLuint vao_ = 0, vbo_ = 0, ibo_ = 0;
		GLsizei  index_count_ = 0; 
	public:

		void create(GLfloat *vertices, unsigned int *indices, unsigned int num_vertices, unsigned int num_indices);
		void render() const;
		void clear();

		Mesh() = default;
		~Mesh();
	
	};
} // end namespace prengine