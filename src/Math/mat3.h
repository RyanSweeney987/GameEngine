#pragma once

#include "mat2.h"
#include "vec3.h"

namespace AirEngine {
	namespace Math {
		struct mat3 {
			// Row major 3x3
			float elements[9];

			mat3();
			mat3(vec3 m0, vec3 m1, vec3 m2);
			mat3(float* elems);

			mat3& add(const mat3& other);
			mat3& subtract(const mat3& other);
			mat3& multiply(const mat3& other);
			mat3& multiply(float scalar);

			float determinant() const;
			mat3 negative() const;
			mat3 inverse() const;
			mat3 transpose() const;

			vec3 getRow(int index) const;
			vec3 getColumn(int index) const;

			std::string toString() const;

			friend std::ostream& operator<<(std::ostream& stream, const mat3& matrix);
		};
	}
}