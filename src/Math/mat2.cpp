#include "mat2.h"

namespace AirEngine {
	namespace Math {
		mat2::mat2() {
			for(int i = 0; i < 4; i++) {
				elements[i] = 0.0f;
			}
		}

		mat2::mat2(vec2 m0, vec2 m1) {
			elements[0] = m0.x;
			elements[1] = m0.y;
			
			elements[2] = m1.x;
			elements[3] = m1.y;
		}

		mat2::mat2(float* elems) {
			std::copy(elems, elems + 4, elements);
		}

		mat2& mat2::add(const mat2& other) {
			for(int i = 0; i < 4; i++) {
				elements[i] += other.elements[i];
			}

			return *this;
		}

		mat2& mat2::subtract(const mat2& other) {
			for(int i = 0; i < 4; i++) {
				elements[i] -= other.elements[i];
			}

			return *this;
		}

		mat2& mat2::multiply(const mat2& other) {
			vec2 row0 = getRow(0);
			vec2 row1 = getRow(1);

			elements[0] = row0.dot(other.getColumn(0));
			elements[1] = row0.dot(other.getColumn(1));

			elements[2] = row1.dot(other.getColumn(0));
			elements[3] = row1.dot(other.getColumn(1));

			return *this;
		}

		mat2& mat2::multiply(float scalar) {
			for(int i = 0; i < 4; i++) {
				elements[i] *= scalar;
			}

			return *this;
		}

		float mat2::determinant() const {
			return elements[0] * elements[3] - elements[1] *  elements[2] ;
		}

		mat2 mat2::negative() const {
			float elems[4];

			std::copy(elements, elements + 4, elems);

			for(int i = 0; i < 4; i++) {
				elems[i] = -elems[i];
			}

			return mat2(elems);
		}

		mat2 mat2::inverse() const {
			float temp[4];

			temp[0] = elements[3];
			temp[1] = -elements[1];
			temp[2] = -elements[2];
			temp[3] = elements[0];
			
			float det = this->determinant();

			for(int i = 0; i < 4; i++) {
				temp[i] *= det;
			}

			return mat2(temp);
		}

		mat2 mat2::transpose() const {
			vec2 row0 = getRow(0);
			vec2 row1 = getRow(1);

			vec2 tranRow0(row0.x, row1.x);
			vec2 tranRow1(row0.y, row1.y);

			return mat2(tranRow0, tranRow1);
		}

		vec2 mat2::getRow(int index) const {
			int row = index * 2;
			return vec2(elements[row], elements[row + 1]);
		}

		vec2 mat2::getColumn(int index) const {
			return vec2(elements[0 + index], elements[2 + index]);
		}

		std::string mat2::toString() const {
			std::stringstream result;
			result << "mat2: (";
			for(int i = 0; i < 3; i++) {
				result << elements[i] << ", ";
			}
			result << elements[3] << ")";
			return result.str();
		}

		std::ostream& operator<<(std::ostream& stream, const mat2& matrix) {
			stream << matrix.toString();
			return stream;
		}
	}
}