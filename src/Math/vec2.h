#pragma once

#include <sstream>
#include <string>

namespace AirEngine {
	namespace Math {
		struct vec2 {
			float x, y;

			vec2();
			vec2(float scalar);
			vec2(float x, float y);
			vec2(const vec2& vector);

			vec2& add(const vec2& other);
			vec2& subtract(const vec2& other);
			vec2& multiply(float scalar);

			const vec2 operator+(const vec2& other);
			const vec2 operator-(const vec2& other);
			const vec2 operator*(float scalar);

			vec2& operator+=(const vec2& other);
			vec2& operator-=(const vec2& other);
			vec2& operator*=(float scalar);

			float magnitude() const;
			vec2 normalise() const;
			float distance(const vec2& other) const;
			float dot(const vec2& other) const;

			std::string toString() const;

			friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
		};
	}
}