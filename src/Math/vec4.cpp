#include "vec4.h"

// TODO Finish
namespace AirEngine {
	namespace Math {
		vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {
		}

		vec4::vec4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {
		}

		vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
		}

		vec4::vec4(vec3 vector, float w) : x(vector.x), y(vector.y), z(vector.z), w(w){
		}

		vec4::vec4(const vec4& vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {
		}

		vec4& vec4::add(const vec4& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		vec4& vec4::add(float scalar) {
			x += scalar;
			y += scalar;
			z += scalar;
			w += scalar;

			return *this;
		}

		vec4& vec4::subtract(const vec4& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}

		vec4& vec4::multiply(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;

			return *this;
		}

		float vec4::dot(const vec4 & other) const {
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		const vec4 vec4::operator+(const vec4& other) {
			vec4 result = *this;
			result += other;
			return result;
		}

		const vec4 vec4::operator-(const vec4 & other) {
			vec4 result = *this;
			result -= other;
			return result;
		}

		const vec4 vec4::operator*(float scalar) {
			vec4 result = *this;
			result *= scalar;
			return result;
		}

		vec4& vec4::operator+=(const vec4& other) {
			return add(other);
		}

		vec4& vec4::operator-=(const vec4 & other) {
			return subtract(other);
		}

		vec4& vec4::operator*=(float scalar) {
			return multiply(scalar);
		}
		
		std::string vec4::toString() const {
			std::stringstream result;
			result << "vec4: (" << x << ", " << y << ", " << z << ", " << w << ")";
			return result.str();
		}
		std::ostream & operator<<(std::ostream & stream, const vec4 & vector) {
			stream << vector.toString();
			return stream;
		}
	}
}


