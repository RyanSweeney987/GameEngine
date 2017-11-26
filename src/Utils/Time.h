#pragma once

#include <GLFW\glfw3.h>

namespace AirEngine {
	namespace Utils {
		class Time {
		public:			
			double getDeltaTime();
			double getCurrentTime();

			void update();
		private:
			double deltaTime;
			double lastTime;
		};
	}
}