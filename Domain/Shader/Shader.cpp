#include "Shader.hpp"
#include <iostream>

using std::cout;
using std::endl;

using std::string;
using std::ifstream;

namespace cgraph {

	Shader::Shader():
	id_{0},
	uniform_model_{0},
	uniform_projection_{0}{

	}

	void Shader::createFromFile(const string& vertex_shader_path, const string& fragment_shader_path) {
		string vertex_str = readFile(vertex_shader_path);
		string frag_str = readFile(fragment_shader_path);
		compile(vertex_str.c_str(), frag_str.c_str());
	}

	void Shader::createFromString(const char* vertex_code, const char* fragment_code) {
		compile(vertex_code, fragment_code);
	}

	string Shader::readFile(const string& file_path) {
		string content = "";
		ifstream sh_file(file_path);
		if (!sh_file.is_open()) {
			cout << "Failed to read " << file_path <<"! File doesn't exist!(?)" << endl;
			return content;
		}

		string line = "";
		while (!sh_file.eof()) {
			std::getline(sh_file, line);
			content.append(line + "\n");
		}

		sh_file.close();
		return content;
	}

	void Shader::compile(const char* vertex_code, const char* fragment_code) {
		id_ = glCreateProgram();
		if (!id_) {
			cout << "shader creation failed!" << endl;
		}

		add(id_, vertex_code, GL_VERTEX_SHADER);
		add(id_, fragment_code, GL_FRAGMENT_SHADER);

		GLint result = 0;
		GLchar eLog[1024] = {0};

		glLinkProgram(id_);
		glGetProgramiv(id_, GL_LINK_STATUS, &result);
		if(!result) {
			glGetProgramInfoLog(id_, sizeof(eLog), NULL, eLog);
			cout << "Error linking program: " <<  eLog << endl;
			return;
		}

		glValidateProgram(id_);
		glGetProgramiv(id_, GL_VALIDATE_STATUS, &result);
		if(!result) {
			glGetProgramInfoLog(id_, sizeof(eLog), NULL, eLog);
			cout << "Error validating program: " <<  eLog << endl;
			return;
		}

		uniform_model_ = glGetUniformLocation(id_, "model");
		uniform_projection_ = glGetUniformLocation(id_, "projection");
	}

	void Shader::use() const {
		glUseProgram(id_);
	}

	GLuint Shader::getProjectionLocation() const {
		return uniform_projection_;
	}

	GLuint Shader::getModelLocation() const {
		return uniform_model_;
	}

	void Shader::clear() {
		if (id_ != 0) {
			glDeleteProgram(id_);
			id_ = 0;
		}

		uniform_projection_ = 0;
		uniform_model_ = 0;
	}

	void Shader::add(GLuint the_program, const char* shader_code, GLenum shader_type) {
		GLuint the_shader = glCreateShader(shader_type);
		const GLchar* the_code = shader_code;

		GLint codeLength = strlen(shader_code);

		glShaderSource(the_shader, 1, &the_code, &codeLength);
		glCompileShader(the_shader);

		GLint result = 0;
		GLchar eLog[1024] = {0};

		glGetShaderiv(the_shader, GL_COMPILE_STATUS, &result);
		if(!result) {
			glGetShaderInfoLog(the_shader, sizeof(eLog), NULL, eLog);
			cout << "Error compiling shaderType: "<< shader_type << " ErrorLog: " <<  eLog <<  endl;
			return;
		}

		glAttachShader(the_program, the_shader);

		return;
	}

	Shader::~Shader() {
		clear();
	}

} // end of namespace cgraph
