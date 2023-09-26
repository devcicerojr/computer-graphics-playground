#include <iostream>
#include <string.h>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>

using namespace std;

const GLint WIDTH = 800 , HEIGHT = 600;

GLuint VAO, VBO, IBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

const float toRadians = 3.14159265f / 180.0f;
float curRotation = 0.0f;
float rotateIncrement = 1.0f;

// Vertex shader
static const char* vShader = "											\n\
#version 330															\n\
																		\n\
layout(location = 0) in vec3 pos;										\n\
out vec4 vCol;															\n\
																		\n\
uniform mat4 model;														\n\
																		\n\
void main() {															\n\
	gl_Position = model * vec4(pos ,  1.0);								\n\
	vCol = vec4(clamp(pos, 0.0, 1.0), 1.0);								\n\
}";


// Fragment Shader
static const char* fShader = "									\n\
#version 330													\n\
																\n\
in vec4 vCol;													\n\
																\n\
out vec4 color;													\n\
																\n\
void main() {													\n\
	color = vCol;												\n\
}";


void createPyramid() {
	unsigned int indices[] = {
		0, 3, 1, // face triangular esquerda
		1, 3, 2, // face triangular direita
		2, 3, 0, // face triangular frontal
		0, 1, 2 // base
	};


	GLfloat vertices[] = {
		-1.0f, -1.0f,  0.0f,
		0.0f, -1.0f, 1.0f, // just added 
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// Creat VAO (vertex array object)
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //binding to VAO

		// Create IBO (index buffer object)
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		// Create VBO (vertex buffer object)
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO); //binding to VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //gives more info about how the vertex buffer object should be interpreted
		glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0); //unbinding from VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbinding from IBO

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

	uniformModel = glGetUniformLocation(shader, "model");
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

	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	createPyramid();
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

		curRotation += rotateIncrement;
		if (curRotation >= 360.0f) {
			curRotation -= 360.0f;
		}

		if (abs(triOffset) >= triMaxOffset) {
			direction = !direction;
		}

		// Clear window
		glClearColor(0.0f, 0.0f , 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader);

		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		model = glm::rotate(model, curRotation * toRadians , glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
		
		 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);


		glfwSwapBuffers(mainWindow);
	}
	

	return 0;
}
