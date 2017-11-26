#include "InputManager.h"

namespace AirEngine {
	namespace Input {
		static bool keysArray[1024];
		bool* InputManager::keys = keysArray;

		static Input::MousePos posArray;
		MousePos* InputManager::mPos = &posArray;

		InputManager::InputManager(Graphics::Window& window) : window(&window) {
			glfwSetKeyCallback(window.getGLFWWindow(), keyCallback);
			glfwSetCursorPosCallback(window.getGLFWWindow(), mouseCallback);
		}

		void InputManager::setKeyboardCallback(void(*function)(GLFWwindow*, int, int, int, int)) {
			glfwSetKeyCallback(window->getGLFWWindow(), function);
		}

		void InputManager::setMouseCallback(void(*function)(GLFWwindow *, double, double)) {
			glfwSetCursorPosCallback(window->getGLFWWindow(), function);
		}

		void InputManager::addInputFunction(void(*function)()) {
			this->functions.push_back(function);
		}

		void InputManager::pollEvents() {
			glfwPollEvents();

			for(auto elem : functions) {
				elem();
			}
		}

		bool InputManager::isKeyPressed(KeyCodes::Keyboard key) {
			//return glfwGetKey(window->getGLFWWindow(), key) == GLFW_PRESS;
			return keys[key];
		}

		MousePos InputManager::getMousePosition() {
			MousePos position;

			glfwGetCursorPos(window->getGLFWWindow(), &position.x, &position.y);

			return position;
		}

		// Action is either GLFW_PRESS | GLFW_REPEAT | GLFW_RELEASE | GLFW_KEY_UNKNOWN
		void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
			if(action == GLFW_PRESS) {
				keys[key] = true;
			} else if(action == GLFW_RELEASE) {
				keys[key] = false;
			}
		}

		void InputManager::mouseCallback(GLFWwindow* window, double xPos, double yPos) {
			mPos->x = xPos;
			mPos->y = yPos;
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