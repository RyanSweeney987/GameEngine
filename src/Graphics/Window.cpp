#include "Window.h"

namespace AirEngine {
	namespace Graphics {
		Window::Window(int width, int height, std::string title) : width(width), height(height), title(title) {
			init();
		}

		Window::~Window() {
			std::cout << "Destroying window" << std::endl;
			terminate();
		}

		GLFWwindow* Window::getGLFWWindow() {
			return window;
		}

		bool Window::isWindowClosed() {
			return glfwWindowShouldClose(window);
		}

		bool Window::isVSyncEnabled() {
			return vSync;
		}

		void Window::setVSyncEnabled(bool enabled) {
			vSync = enabled;
			glfwSwapInterval(enabled);
		}

		void Window::init() {
			std::cout << "Creating window: " << width << " by " << height << " - \"" << title.c_str() << "\"" << std::endl;

			if(glfwInit()) {
				const GLchar* extensions = glfwGetVersionString();

				std::cout << extensions << std::endl;

				// Set all the required options for GLFW
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
				glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

				// Create a GLFWwindow object that we can use for GLFW's functions
				window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
				if(window == nullptr) {
					std::cout << "Failed to create GLFW window" << std::endl;
					glfwTerminate();

					// Throw exception
					return;
				}
				glfwMakeContextCurrent(window);
				glfwSwapInterval(0);

				// Set this to true so GLEW knows to use a modern approach to 
				// retrieving function pointers and extensions
				glewExperimental = GL_TRUE;
				// Initialize GLEW to setup the OpenGL Function pointers
				if(glewInit() != GLEW_OK) {
					std::cout << "Failed to initialize GLEW" << std::endl;

					// Throw exception in little error window
					return;
				}

				glViewport(0, 0, width, height);

				glEnable(GL_DEPTH_TEST);
			}
		}

		void Window::closeWindow() {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		void Window::terminate() {
			if(glfwGetCurrentContext()) {
				std::cout << "Destroying GLContext" << std::endl;
				glfwTerminate();
			}
		}
	}
}