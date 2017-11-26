#pragma once

#include <vector>

#include "../Graphics/Window.h"

namespace AirEngine {
	namespace Input {
		namespace KeyCodes {
			enum Keyboard {
				KEY_A = GLFW_KEY_A, KEY_B = GLFW_KEY_B, KEY_C = GLFW_KEY_C,
				KEY_D = GLFW_KEY_D, KEY_E = GLFW_KEY_E, KEY_F = GLFW_KEY_F,
				KEY_G = GLFW_KEY_G, KEY_H = GLFW_KEY_H, KEY_I = GLFW_KEY_I,
				KEY_J = GLFW_KEY_J, KEY_K = GLFW_KEY_K, KEY_L = GLFW_KEY_L,
				KEY_M = GLFW_KEY_M, KEY_N = GLFW_KEY_N, KEY_O = GLFW_KEY_O,
				KEY_P = GLFW_KEY_P, KEY_Q = GLFW_KEY_Q, KEY_R = GLFW_KEY_R,
				KEY_S = GLFW_KEY_S, KEY_T = GLFW_KEY_T, KEY_U = GLFW_KEY_U,
				KEY_V = GLFW_KEY_V, KEY_W = GLFW_KEY_W, KEY_X = GLFW_KEY_X,
				KEY_Y = GLFW_KEY_Y, KEY_Z = GLFW_KEY_Z,

				KEY_1 = GLFW_KEY_1, KEY_2 = GLFW_KEY_2, KEY_3 = GLFW_KEY_3,
				KEY_4 = GLFW_KEY_4, KEY_5 = GLFW_KEY_5, KEY_6 = GLFW_KEY_6,
				KEY_7 = GLFW_KEY_7, KEY_8 = GLFW_KEY_8, KEY_9 = GLFW_KEY_9,
				KEY_0 = GLFW_KEY_0,

				KEY_ESC = GLFW_KEY_ESCAPE,

				KEY_PRESS = GLFW_PRESS, KEY_RELEASE = GLFW_RELEASE
			};

			enum Mouse {
			};
		}

		struct MousePos {
			double x, y;
		};

		class InputManager {
		public:
			InputManager(Graphics::Window& window);

			void setKeyboardCallback(void(*function)(GLFWwindow*, int, int, int, int));
			void setMouseCallback(void(*function)(GLFWwindow*, double, double));

			void addInputFunction(void(*function)());

			void pollEvents();

			bool isKeyPressed(KeyCodes::Keyboard key);

			MousePos getMousePosition();
		private:
			Graphics::Window* window;
			std::vector<void (*)()> functions;

			static bool* keys;
			static MousePos* mPos;

			static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
			static void mouseCallback(GLFWwindow* window, double xPos, double yPos);
		};
	}
}