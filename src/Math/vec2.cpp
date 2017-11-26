#include "vec2.h"

namespace AirEngine {
	namespace Math {
		vec2::vec2() : x(0.0f), y(0.0f) {
		}

		vec2::vec2(float scalar) : x(scalar), y(scalar) {
		}

		vec2::vec2(float x, float y) : x(x), y(y) {
		}

		vec2::vec2(const vec2& vector) : x(vector.x), y(vector.y) {
		}

		vec2& vec2::add(const vec2& other) {
			x += other.x;
			y += other.y;

			return *this;
		}
		
		vec2& vec2::subtract(const vec2& other) {
			x -= other.x;
			y -= other.y;

			return *this;
		}

		vec2& vec2::multiply(float scalar) {
			x *= scalar;
			y *= scalar;

			return *this;
		}

		float vec2::magnitude() const {
			return sqrtf(x*x + y*y);
		}

		vec2 vec2::normalise() const {
			float length = magnitude();
			return vec2(x / length, y / length);
		}

		float vec2::distance(const vec2& other) const {
			float a = x - other.x;
			float b = y - other.y;
			return sqrtf(a*a + b*b);
		}

		float vec2::dot(const vec2& other) const {
			return x * other.x + y * other.y;
		}
		
		const vec2 vec2::operator+(const vec2& other) {
			vec2 result = *this;
			result += other;
			return result;
		}

		const vec2 vec2::operator-(const vec2& other) {
			vec2 result = *this;
			result -= other;
			return result;
		}
		
		const vec2 vec2::operator*(float scalar) {
			vec2 result = *this;
			result *= scalar;
			return result;
		}

		vec2& vec2::operator+=(const vec2& other) {
			return add(other);
		}

		vec2& vec2::operator-=(const vec2& other) {
			return subtract(other);
		}

		vec2& vec2::operator*=(float scalar) {
			return multiply(scalar);
		}

		std::string vec2::toString() const {
			std::stringstream result;
			result << "vec2: (" << x << ", " << y << ")";
			return result.str();
		}

		std::ostream& operator<<(std::ostream & stream, const vec2& vector) {
			stream << vector.toString();
			return stream;
		}
	}
}