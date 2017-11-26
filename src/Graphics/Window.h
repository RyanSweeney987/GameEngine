#pragma once

// GLEW
#define GLEW_STATIC
#include <gl/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

namespace AirEngine {
	namespace Graphics {
		class Window {
		public:
			Window(int width, int height, const std::string title);
			~Window();

			GLFWwindow* getGLFWWindow();
			bool isWindowClosed();
			bool isVSyncEnabled();

			void setVSyncEnabled(bool enabled);

			void closeWindow();
			void terminate();
		private:
			GLFWwindow* window;
			GLuint width, height;
			std::string title;
			bool vSync;

			void init();
		};
	}
}