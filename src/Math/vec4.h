#pragma once

#include <sstream>
#include <string>

#include "vec3.h"

// TODO Finish
namespace AirEngine {
	namespace Math {
		struct vec4 {
			float x, y, z, w;

			vec4();
			vec4(float scalar);
			vec4(float x, float y, float z, float w);
			vec4(vec3 vector, float w);

			vec4(const vec4& vector);

			vec4& add(const vec4& other);
			vec4& add(float scalar);
			vec4& subtract(const vec4& other);
			vec4& multiply(float scalar);

			const vec4 operator+(const vec4& other);
			const vec4 operator-(const vec4& other);
			const vec4 operator*(float scalar);

			vec4& operator+=(const vec4& other);
			vec4& operator-=(const vec4& other);
			vec4& operator*=(float scalar);

			float dot(const vec4& other) const;

			std::string toString() const;

			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
		};
	}
}