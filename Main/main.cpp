#include <iostream>
#include <string.h>
#include <cmath>
// TODO: Include logic here for other OSes
#ifdef _WIN32
	#include <Windows.h>
#endif


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <Mesh/Mesh.hpp>
#include <Shader/Shader.hpp>
#include <memory>
#include <filesystem>

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::endl;
using std::filesystem::path;

using cgraph::Mesh;
using cgraph::Shader;

vector<shared_ptr<Mesh>> meshes;
vector<shared_ptr<Shader>> shaders;

const GLint WIDTH = 800 , HEIGHT = 600;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

const float toRadians = 3.14159265f / 180.0f;
float curRotation = 0.0f;
float rotateIncrement = 1.0f;

path GetExecutablePath() {
		path executable_path;

// TODO: Add logic here for other OSes
#ifdef _WIN32
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		executable_path = buffer;
#endif

		return executable_path;
}

static const path v_shader_path = GetExecutablePath().parent_path().append("shader.vert");
static const path f_shader_path = GetExecutablePath().parent_path().append("shader.frag");

// Vertex shader
static const string vShader = v_shader_path.string();


// Fragment Shader
static const string fShader = f_shader_path.string();



void createShaders() {
	auto shader1 = make_shared<Shader>();
	shader1->createFromFile(vShader, fShader);
	shaders.push_back(shader1);
}

void createObjects() {
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

	shared_ptr<Mesh> pyramid_mesh = make_shared<Mesh>();
	pyramid_mesh->create(vertices, indices, 12, 12);
	shared_ptr<Mesh> pyramid_mesh2 = make_shared<Mesh>();
	pyramid_mesh2->create(vertices, indices, 12, 12);

	meshes.push_back(pyramid_mesh);
	meshes.push_back(pyramid_mesh2);
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

	createObjects();
	createShaders();

	GLuint uniformModel = 0, uniformProjection = 0;

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth/(GLfloat)bufferHeight, 0.1f, 100.0f);

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

		shaders[0]->use();
		uniformModel = shaders[0]->getModelLocation();
		uniformProjection = shaders[0]->getProjectionLocation();

		glm::mat4 model(1.0f);
		glm::mat4 model2(1.0f);

		model = glm::translate(model, glm::vec3(-0.5f, triOffset, -2.5f));
		//model = glm::rotate(model, curRotation * toRadians , glm::vec3(0.0f, 1.0f, 0.0f));	 
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));


		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshes[0]->render();

		model2 = glm::translate(model2, glm::vec3(0.5f, -triOffset, -2.5f));
		//model2 = glm::rotate(model2, curRotation * toRadians , glm::vec3(1.0f, 0.0f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model2));

		meshes[1]->render();


		glUseProgram(0);


		glfwSwapBuffers(mainWindow);
	}
	

	return 0;
}
