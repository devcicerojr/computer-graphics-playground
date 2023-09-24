#include <iostream>
#include <string.h>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

const GLint WIDTH = 800 , HEIGHT = 600;

GLuint VAO, VBO, shader, uniformXMove;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

// Vertex shader
static const char* vShader = "											\n\
#version 330															\n\
																		\n\
layout(location = 0) in vec3 pos;										\n\
																		\n\
uniform float xMove;													\n\
																		\n\
void main() {															\n\
	gl_Position = vec4(0.4 * pos.x + xMove, 0.4 * pos.y, pos.z, 1.0);	\n\
}";


// Fragment Shader
static const char* fShader = "									\n\
#version 330													\n\
																\n\
out vec4 color;													\n\
																\n\
void main() {													\n\
	color = vec4(1.0, 0.0, 0.0, 1.0);							\n\
}";

void createTriangle() {
	GLfloat vertices[] = {
		-1.0f, -1.0f,  0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// Creat VAO (vertex array object)
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //binding to VAO

		// Create VBO (vertex buffer object)
		glGenBuffers(1 , &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO); //binding to VBO
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinding from VBO

	glBindVertexArray(0); //unbinding from VAO
}

void addShader(GLuint program, const char* shader_code, GLenum shader_type) {
	GLuint the_shader = glCreateShader(shader_type);
	const GLchar* the_code = shader_code;

	GLint codeLength = strlen(shader_code);

	glShaderSource(the_shader, 1, &the_code, &codeLength);
	glCompileShader(the_shader);

	GLint result = 0;
	GLchar eLog[1024] = {0};

	glGetShaderiv(the_shader, GL_COMPILE_STATUS, &result);
	if(!result) {
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error compiling shaderType: "<< shader_type << " ErrorLog: " <<  eLog <<  endl;
		return;
	}

	glAttachShader(program, the_shader);

	return;
}

void compileShaders() {
	shader = glCreateProgram();
	if (!shader) {
		cout << "shader creation failed!" << endl;
	}

	addShader(shader, vShader, GL_VERTEX_SHADER);
	addShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = {0};

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if(!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error linking program: " <<  eLog << endl;
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if(!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error validating program: " <<  eLog << endl;
		return;
	}

	uniformXMove = glGetUniformLocation(shader, "xMove");
}

int main() {
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

	createTriangle();
	compileShaders();

	while (!glfwWindowShouldClose(mainWindow)) {
		// Get and Handle User Input Events
		glfwPollEvents();

		if (direction) {
			triOffset += triIncrement;
		}
		else {
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxOffset) {
			direction = !direction;
		}

		// Clear window
		glClearColor(0.0f, 0.0f , 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);
		glUniform1f(uniformXMove, triOffset);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);


		glfwSwapBuffers(mainWindow);
	}
	

	return 0;
}
