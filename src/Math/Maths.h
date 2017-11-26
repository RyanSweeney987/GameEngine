#pragma once

#include <glm/glm.hpp>

#include <cmath>

namespace AirEngine {
	namespace Math {
		//#define PI 
		//#define TAU PI*2.0f;
		const float PI = 3.14159265358f;
		const float TAU = 6.28318530716f;
		
		inline float toRadians(float degrees) {
			return degrees * (PI / 180.0f);
		}

		inline float toDegrees(float radians) {
			return radians * (180.0f / PI);
		}

		inline int sign(float value) {
			return (value > 0) - (value < 0);
		}

		inline float sin(float angle) {
			return sinf(angle);
		}

		inline float cos(float angle) {
			return cosf(angle);
		}

		inline float tan(float angle) {
			return tanf(angle);
		}

		inline float sqrt(float value) {
			return sqrtf(value);
		}

		inline float rsqrt(float value) {
			return 1.0f / sqrtf(value);
		}

		inline float asin(float value) {
			return asinf(value);
		}

		inline float acos(float value) {
			return acosf(value);
		}

		inline float atan(float value) {
			return atanf(value);
		}

		inline float atan2(float y, float x) {
			return atan2f(y, x);
		}

		inline float minVal(float value, float minimum) {
			return (value < minimum) ? minimum : value;
		}

		inline float maxVal(float value, float maximum) {
			return (value > maximum) ? maximum : value;
		}

		inline float clamp(float value, float minimum, float maximum) {
			return (value > minimum) ? (value < maximum) ? value : maximum : minimum;
		}
	}
}