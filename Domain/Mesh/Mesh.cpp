#include "Mesh.hpp"

namespace cgraph {

	void Mesh::create(GLfloat *vertices, unsigned int *indices, unsigned int num_vertices, unsigned int num_indices) {
		index_count_ = num_indices;
		// Creat VAO (vertex array object)
		glCreateVertexArrays(1, &vao_);
		glBindVertexArray(vao_); //binding to VAO

		// Create IBO (index buffer object)
		glGenBuffers(1, &ibo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * num_indices, indices, GL_STATIC_DRAW);
		
		// Create VBO (vertex buffer object)
		glGenBuffers(1, &vbo_);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_); //binding to VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * num_vertices, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //gives more info about how the vertex buffer object should be interpreted
		glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbinding from IBO
		//glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinding from VBO (not needed because VBO is only unbound if I bind a different one)
		// or when I call glBindVertexArray(0) that unbinds from the VAO

		glBindVertexArray(0); //unbinding from VAO
	}

	void Mesh::render() const {
		if (vao_ == 0 || ibo_ == 0 || index_count_ == 0) {
			return;
		}

		glBindVertexArray(vao_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
		glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::clear() {
		if (ibo_ != 0) {
			glDeleteBuffers(1, &ibo_);
			ibo_ = 0;
		}
		if (vbo_ != 0) {
			glDeleteBuffers(1, &vbo_);
			vbo_ = 0;
		}
		if (vao_ != 0) {
			glDeleteVertexArrays(1, &vao_);
			vao_ = 0;
		}

		index_count_ = 0;
	}

	Mesh::~Mesh() {
		clear();
	}

} // end of namespace cgraph
