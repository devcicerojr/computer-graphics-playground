#include "Camera.hpp"

using glm::vec3;
using glm::radians;
using glm::normalize;
using glm::cross;
using glm::mat4;
using glm::lookAt;

namespace cgraph {

	Camera::Camera() : 
	position_{0.0f, 0.0f, 0.0f},
	front_{0.0f, 0.0f, -1.0f},
	up_{0.0f, 1.0f, 0.0f},
	right_{1.0f, 0.0f, 0.0f},
	world_up_{0.0f, 1.0f, 0.0f},
	yaw_{0.0f},
	pitch_{0.0f},
	move_speed_{5.0f},
	turn_speed_{2.0f} {

	}

	Camera::Camera(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch, GLfloat move_speed, GLfloat turn_speed) :
	position_{position},
	front_{0.0f, 0.0f, -1.0f},
	up_{up},
	right_{1.0f, 0.0f, 0.0f},
	world_up_{up},
	yaw_{yaw},
	pitch_{pitch},
	move_speed_{move_speed},
	turn_speed_{turn_speed}{

	}

	void Camera::update() {
		front_.x = cos(radians(yaw_)) * cos(radians(pitch_));
		front_.y = sin(radians(pitch_));
		front_.z = sin(radians(yaw_)) * cos(radians(pitch_));
		front_ = normalize(front_);

		right_ = normalize(cross(front_, world_up_));
		up_ = normalize(cross(right_, front_));
	}


	// ostream& operator<<(ostream& os, const glm::vec3& v) {
	// 	os << v.x << ", " << v.y << ", " << v.z;
	// 	return os;
	// }

	void Camera::keyControl(bool* keys) {
		
		if (keys[GLFW_KEY_W]) {
			position_ += front_ * move_speed_;
		}
		if (keys[GLFW_KEY_S]) {
			position_ -= front_ * move_speed_;
		}
		if (keys[GLFW_KEY_A]) {
			position_ -= right_ * move_speed_;
		}
		if (keys[GLFW_KEY_D]) {
			position_ += right_ * move_speed_;
		}
	}

	mat4 Camera::calculateViewMatrix() const {
		return lookAt(position_, position_ + front_, up_);
	}

} // end of namespace cgraph