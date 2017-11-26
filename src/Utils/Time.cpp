#include "Time.h"

namespace AirEngine {
	namespace Utils {
		double Time::getDeltaTime() {
			return deltaTime;
		}

		double Time::getCurrentTime() {
			return glfwGetTime();
		}

		void Time::update() {
			double currentTime = glfwGetTime();

			deltaTime = currentTime - lastTime;
			lastTime = currentTime;
		}
	}
}