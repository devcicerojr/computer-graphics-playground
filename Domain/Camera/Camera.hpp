#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using glm::vec3;
using glm::mat4;

namespace cgraph {

	class Camera {
	private:
		vec3 position_;
		vec3 front_;
		vec3 up_;
		vec3 right_;
		vec3 world_up_;

		GLfloat yaw_;
		GLfloat pitch_;

		GLfloat move_speed_;
		GLfloat turn_speed_; 

		void update();
	public:
		Camera();
		Camera(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch, GLfloat move_speed, GLfloat turn_speed);
		~Camera() = default;


		void keyControl(bool* keys);
		mat4 calculateViewMatrix() const;
	};
} // end of namespace cgraph