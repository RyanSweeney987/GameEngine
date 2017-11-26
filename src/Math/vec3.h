#pragma once

#include <glm/glm.hpp>

#include <sstream>
#include <string>

#include "vec2.h"

namespace AirEngine {
	namespace Math {
		struct vec3 {
			float x, y, z;

			vec3();
			vec3(float scalar);
			vec3(float x, float y, float z);
			vec3(vec2 vector, float z);

			vec3(const vec3& vector);

			vec3& add(const vec3& other);
			vec3& subtract(const vec3& other);
			vec3& multiply(float scalar);

			const vec3 operator+(const vec3& other);
			const vec3 operator-(const vec3& other);
			friend const vec3 operator-(const vec3& left, const vec3& right);
			const vec3 operator*(float scalar);

			vec3& operator+=(const vec3& other);
			vec3& operator-=(const vec3& other);
			vec3& operator*=(float scalar);

			float magnitude() const;
			vec3 normalise() const;
			float distance(const vec3& other) const;
			float dot(const vec3& other) const;
			vec3 cross(const vec3& other) const;

			std::string toString() const;

			friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
		};
	}
}