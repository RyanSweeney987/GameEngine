#include "vec3.h"

namespace AirEngine {
	namespace Math {
		vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {
		}

		vec3::vec3(float scalar) : x(scalar), y(scalar), z(scalar) {
		}

		vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {
		}

		vec3::vec3(vec2 vector, float z) : x(vector.x), y(vector.y), z(z) {
		}

		vec3::vec3(const vec3& vector) : x(vector.x), y(vector.y), z(vector.z) {
		}

		vec3& vec3::add(const vec3& other) {
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3& vec3::subtract(const vec3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		vec3& vec3::multiply(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		float vec3::magnitude() const {
			return sqrtf(x*x + y*y + z*z);
		}

		vec3 vec3::normalise() const {
			float length = magnitude();
			return vec3(x / length, y / length, z / length);
		}

		float vec3::distance(const vec3& other) const {
			float a = x - other.x;
			float b = y - other.y;
			float c = z - other.z;
			return sqrtf(a*a + b*b + c*c);
		}

		float vec3::dot(const vec3& other) const {
			return x * other.x + y * other.y + z * other.z;
		}

		vec3 vec3::cross(const vec3& other) const {
			return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y );
		}

		const vec3 vec3::operator+(const vec3& other) {
			vec3 result = *this;
			result += other;
			return result;
		}

		const vec3 vec3::operator-(const vec3& other) {
			vec3 result = *this;
			result -= other;
			return result;
		}

		const vec3 operator-(const vec3& left, const vec3& right) {
			vec3 result = left;
			result.subtract(right);
			return result;
		}

		const vec3 vec3::operator*(const float scalar) {
			vec3 result = *this;
			result *= scalar;
			return result;
		}

		vec3& vec3::operator+=(const vec3& other) {
			return add(other);
		}

		vec3& vec3::operator-=(const vec3& other) {
			return subtract(other);
		}

		vec3& vec3::operator*=(const float scalar) {
			return multiply(scalar);
		}

		std::string vec3::toString() const {
			std::stringstream result;
			result << "vec3: (" << x << ", " << y << ", " << z << ")";
			return result.str();
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
			stream << vector.toString();
			return stream;
		}

	}
}