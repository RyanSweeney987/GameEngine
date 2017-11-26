#include "Camera.h"

namespace AirEngine {
	namespace Entity {
		Camera::Camera(Math::vec3 position, Math::vec3 front, Math::vec3 up) : position(position), 
			front(front), up(up), fov(45.0f), aspectRatio(1280.0f / 720.0f), nearClip(0.1f),
			farClip(100.0f) {
		}

		Camera::Camera(Math::vec3 position, Math::vec3 front, Math::vec3 up, float fov, float aspectRatio, 
			float near, float far) : position(position), front(front), up(up), fov(fov), aspectRatio(aspectRatio),
			nearClip(near), farClip(far) {
		}

		Math::mat4 Camera::getViewMatrix() {
			return Math::mat4().lookAt(position, front, up);
		}

		Math::mat4 Camera::getProjectionMatrix() {
			return Math::mat4().perspective(fov, aspectRatio, nearClip, farClip);
		}

		void Camera::setPosition(Math::vec3 position) {
			this->position = position;
		}
	}
}

/*void mouse_callback(GLFWwindow * window, double xPos, double yPos) {
	if(firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	GLfloat sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if(pitch > 89.0f) {
		pitch = 89.0f;
	}
	if(pitch < -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(front);
}

void do_movement() {
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if(keys[GLFW_KEY_W]) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if(keys[GLFW_KEY_S]) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if(keys[GLFW_KEY_A]) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if(keys[GLFW_KEY_D]) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if(action == GLFW_PRESS) {
			keys[key] = true;
	} else if(action == GLFW_RELEASE) {
		keys[key] = false;
	}
}
 */