#pragma once

#include <sstream>
#include <iostream>
#include <string>

#include "Maths.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"

namespace AirEngine {
	namespace Math {
		struct mat4 {
			// Row major 4x4
			float elements[16];

			mat4();
			mat4(float diagonal);
			mat4(vec4 m0, vec4 m1, vec4 m2, vec4 m3);
			mat4(float* elems);

			mat4& add(const mat4& other);
			mat4& subtract(const mat4& other);
			mat4& multiply(const mat4& other);
			mat4& multiply(float scalar);

			const mat4 operator+(const mat4& other);
			const mat4 operator-(const mat4& other);
			const mat4 operator*(const mat4& other);
			const mat4 operator*(float scalar);

			mat4& operator+=(const mat4& other);
			mat4& operator-=(const mat4& other);
			mat4& operator*=(const mat4& other);
			mat4& operator*=(float scalar);

			float determinant() const;
			mat4 negative() const;
			mat4 inverse() const;
			mat4 transpose() const;

			// Camera related
			mat4 orthographic(float left, float right, float bottom, float top, float near, float far) const;
			mat4 perspective(float fov, float aspectRatio, float near, float far) const;
			mat4 lookAt(const vec3& camera, const vec3& target, const vec3& up) const;

			// Position related

			mat4 translate(const vec3& translation) const;
			mat4 rotate(float radians, const vec3& axis) const;
			mat4 scale(const vec3& scale) const;

			vec4 getRow(int index) const;
			vec4 getColumn(int index) const;

			std::string toString() const;

			friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);
		};
	}
}