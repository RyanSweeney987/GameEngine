#include "mat3.h"

namespace AirEngine {
	namespace Math {
		mat3::mat3() {
			for(int i = 0; i < 9; i++) {
				elements[i] = 0.0f;
			}
		}

		mat3::mat3(vec3 m0, vec3 m1, vec3 m2) {
			elements[0] = m0.x;
			elements[1] = m0.y;
			elements[2] = m0.z;

			elements[3] = m1.x;
			elements[4] = m1.y;
			elements[5] = m1.z;

			elements[6] = m2.x;
			elements[7] = m2.y;
			elements[8] = m2.z;
		}

		mat3::mat3(float* elems) {
			std::copy(elems, elems + 9, elements);
		}

		mat3& mat3::add(const mat3& other) {
			for(int i = 0; i < 9; i++) {
				elements[i] += other.elements[i];
			}

			return *this;
		}

		mat3& mat3::subtract(const mat3& other) {
			for(int i = 0; i < 9; i++) {
				elements[i] -= other.elements[i];
			}

			return *this;
		}

		mat3& mat3::multiply(const mat3& other) {
			vec3 row0 = getRow(0);
			vec3 row1 = getRow(1);
			vec3 row2 = getRow(2);

			elements[0] = row0.dot(other.getColumn(0));
			elements[1] = row0.dot(other.getColumn(1));
			elements[2] = row0.dot(other.getColumn(2));

			elements[3] = row1.dot(other.getColumn(0));
			elements[4] = row1.dot(other.getColumn(1));
			elements[5] = row1.dot(other.getColumn(2));

			elements[6] = row2.dot(other.getColumn(0));
			elements[7] = row2.dot(other.getColumn(1));
			elements[8] = row2.dot(other.getColumn(2));

			return *this;
		}

		mat3& mat3::multiply(float scalar) {
			for(int i = 0; i < 9; i++) {
				elements[i] *= scalar;
			}

			return *this;
		}

		float mat3::determinant() const {
			float val1 = elements[0] * elements[4] * elements[8];
			float val2 = elements[1] * elements[5] * elements[6];
			float val3 = elements[2] * elements[3] * elements[7];

			float val4 = elements[2] * elements[4] * elements[6];
			float val5 = elements[0] * elements[5] * elements[7];
			float val6 = elements[1] * elements[3] * elements[8];

			return (val1 + val2 + val3) - (val4 - val5 - val6);
		}

		mat3 mat3::negative() const {
			float elems[9];

			std::copy(elements, elements + 9, elems);

			for(int i = 0; i < 9; i++) {
				elems[i] = -elems[i];
			}

			return mat3(elems);
		}

		mat3 mat3::inverse() const {
			// Matrix of minors
			float f00[4] {elements[4], elements[5], elements[7], elements[8]};
			float f01[4] {elements[3], elements[5], elements[6], elements[8]};
			float f02[4] {elements[3], elements[4], elements[6], elements[7]};

			float f10[4] {elements[1], elements[2], elements[7], elements[8]};
			float f11[4] {elements[0], elements[2], elements[6], elements[8]};
			float f12[4] {elements[0], elements[1], elements[6], elements[7]};

			float f20[4] {elements[1], elements[2], elements[4], elements[5]};
			float f21[4] {elements[0], elements[2], elements[3], elements[5]};
			float f22[4] {elements[0], elements[1], elements[3], elements[4]};
			
			float mat[9] {mat2(f00).determinant(), mat2(f01).determinant(), mat2(f02).determinant(),
				mat2(f10).determinant(), mat2(f11).determinant(), mat2(f12).determinant(),
				mat2(f20).determinant(), mat2(f21).determinant(), mat2(f22).determinant()};

			// Matrix of cofactors
			mat[1] = -mat[1];
			mat[3] = -mat[3];
			mat[5] = -mat[5];
			mat[7] = -mat[7];

			// Adjugate
			mat3 adj = mat3(mat).transpose();

			// Multiply by determinant
			return adj.multiply(this->determinant());
		}

		mat3 mat3::transpose() const {
			vec3 row0 = getRow(0);
			vec3 row1 = getRow(1);
			vec3 row2 = getRow(2);

			vec3 tranRow0(row0.x, row1.x, row2.x);
			vec3 tranRow1(row0.y, row1.y, row2.y);
			vec3 tranRow2(row0.z, row1.z, row2.z);

			return mat3(tranRow0, tranRow1, tranRow2);
		}

		vec3 mat3::getRow(int index) const {
			int row = index * 3;
			return vec3(elements[row], elements[row + 1], elements[row + 2]);
		}

		vec3 mat3::getColumn(int index) const {
			return vec3(elements[0 + index], elements[3 + index], elements[6 + index]);
		}

		std::string mat3::toString() const {
			std::stringstream result;
			result << "mat3: (";
			for(int i = 0; i < 8; i++) {
				result << elements[i] << ", ";
			}
			result << elements[8] << ")";
			return result.str();
		}

		std::ostream & operator<<(std::ostream& stream, const mat3& matrix) {
			stream << matrix.toString();
			return stream;
		}
	}
}