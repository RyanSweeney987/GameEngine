#pragma once

#include <iostream>

#include "vec2.h"

namespace AirEngine {
	namespace Math {
		struct mat2 {
			// Row major 2x2
			float elements[4];

			mat2();
			mat2(vec2 m0, vec2 m1);
			mat2(float* elems);

			mat2& add(const mat2& other);
			mat2& subtract(const mat2& other);
			mat2& multiply(const mat2& other);
			mat2& multiply(float scalar);

			float determinant() const;
			mat2 negative() const;
			mat2 inverse() const;
			mat2 transpose() const;

			vec2 getRow(int index) const;
			vec2 getColumn(int index) const;

			std::string toString() const;
			
			friend std::ostream& operator<<(std::ostream& stream, const mat2& matrix);
		};
	}
}