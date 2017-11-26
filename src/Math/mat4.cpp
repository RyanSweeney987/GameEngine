#include "mat4.h"

namespace AirEngine {
	namespace Math {
		mat4::mat4() {
			for(int i = 0; i < 16; i++) {
				elements[i] = 0.0f;
			}
		}

		mat4::mat4(float diagonal) {
			for(int i = 0; i < 16; i++) {
				elements[i] = 0.0f;
			}

			elements[0] = diagonal;
			elements[5] = diagonal;
			elements[10] = diagonal;
			elements[15] = diagonal;
		}

		mat4::mat4(vec4 m0, vec4 m1, vec4 m2, vec4 m3) {
			elements[0] = m0.x;
			elements[1] = m0.y;
			elements[2] = m0.z;
			elements[3] = m0.w;

			elements[4] = m1.x;
			elements[5] = m1.y;
			elements[6] = m1.z;
			elements[7] = m1.w;

			elements[8] = m2.x;
			elements[9] = m2.y;
			elements[10] = m2.z;
			elements[11] = m2.w;

			elements[12] = m3.x;
			elements[13] = m3.y;
			elements[14] = m3.z;
			elements[15] = m3.w;
		}

		mat4::mat4(float* elems) {
			std::copy(elems, elems + 16, elements);
		}

		mat4& mat4::add(const mat4& other) {
			for(int i = 0; i < 16; i++) {
				elements[i] += other.elements[i];
			}

			return *this;
		}

		mat4& mat4::subtract(const mat4& other) {
			for(int i = 0; i < 16; i++) {
				elements[i] -= other.elements[i];
			}

			return *this;
		}

		mat4& mat4::multiply(const mat4& other) {
			vec4 row0 = getRow(0);
			vec4 row1 = getRow(1);
			vec4 row2 = getRow(2);
			vec4 row3 = getRow(3);

			elements[0] = row0.dot(other.getColumn(0));
			elements[1] = row0.dot(other.getColumn(1));
			elements[2] = row0.dot(other.getColumn(2));
			elements[3] = row0.dot(other.getColumn(3));

			elements[4] = row1.dot(other.getColumn(0));
			elements[5] = row1.dot(other.getColumn(1));
			elements[6] = row1.dot(other.getColumn(2));
			elements[7] = row1.dot(other.getColumn(3));

			elements[8] = row2.dot(other.getColumn(0));
			elements[9] = row2.dot(other.getColumn(1));
			elements[10] = row2.dot(other.getColumn(2));
			elements[11] = row2.dot(other.getColumn(3));

			elements[12] = row3.dot(other.getColumn(0));
			elements[13] = row3.dot(other.getColumn(1));
			elements[14] = row3.dot(other.getColumn(2));
			elements[15] = row3.dot(other.getColumn(3));

			return *this;
		}

		mat4& mat4::multiply(float scalar) {
			for(int i = 0; i < 16; i++) {
				elements[i] *= scalar;
			}

			return *this;
		}

		const mat4 mat4::operator+(const mat4& other) {
			mat4 result = *this;
			result += other;
			return result;
		}

		const mat4 mat4::operator-(const mat4& other) {
			mat4 result = *this;
			result -= other;
			return result;
		}

		const mat4 mat4::operator*(const mat4& other) {
			mat4 result = *this;
			result -= other;
			return result;
		}

		const mat4 mat4::operator*(float scalar) {
			mat4 result = *this;
			result *= scalar;
			return result;
		}

		mat4& mat4::operator+=(const mat4& other) {
			return add(other);
		}

		mat4& mat4::operator-=(const mat4& other) {
			return subtract(other);
		}

		mat4& mat4::operator*=(const mat4& other) {
			return multiply(other);
		}

		mat4& mat4::operator*=(float scalar) {
			return multiply(scalar);
		}

		float mat4::determinant() const {
			float f00[9] {elements[5], elements[6], elements[7],
				elements[9], elements[10], elements[11],
				elements[13], elements[14], elements[15]};

			float f01[9] {elements[4], elements[6], elements[7],
				elements[8], elements[10], elements[11],
				elements[12], elements[14], elements[15]};

			float f02[9] {elements[4], elements[5], elements[7],
				elements[8], elements[9], elements[11],
				elements[12], elements[13], elements[15]};

			float f03[9] {elements[4], elements[5], elements[6],
				elements[8], elements[9], elements[10],
				elements[12], elements[13], elements[14]};

			float det = (elements[0] * mat3(f00).determinant()) - (elements[1] * mat3(f01).determinant())
				+ (elements[2] * mat3(f02).determinant()) - (elements[3] * mat3(f03).determinant());

			return det;
		}

		mat4 mat4::negative() const {
			float elems[16];

			std::copy(elements, elements + 16, elems);

			for(int i = 0; i < 16; i++) {
				elems[i] = -elems[i];
			}

			return mat4(elems);
		}

		mat4 mat4::inverse() const {
			// Matrix of minors
			float f00[9] {elements[4], elements[5], elements[7], elements[8]};
			float f01[9] {elements[3], elements[5], elements[6], elements[8]};
			float f02[9] {elements[3], elements[4], elements[6], elements[7]};
			float f03[9] {elements[3], elements[4], elements[6], elements[7]};

			float f10[9] {elements[1], elements[2], elements[7], elements[8]};
			float f11[9] {elements[0], elements[2], elements[6], elements[8]};
			float f12[9] {elements[0], elements[1], elements[6], elements[7]};
			float f13[9] {elements[3], elements[4], elements[6], elements[7]};

			float f20[9] {elements[1], elements[2], elements[4], elements[5]};
			float f21[9] {elements[0], elements[2], elements[3], elements[5]};
			float f22[9] {elements[0], elements[1], elements[3], elements[4]};
			float f23[9] {elements[3], elements[4], elements[6], elements[7]};

			float f30[9] {elements[1], elements[2], elements[4], elements[5]};
			float f31[9] {elements[0], elements[2], elements[3], elements[5]};
			float f32[9] {elements[0], elements[1], elements[3], elements[4]};
			float f33[9] {elements[3], elements[4], elements[6], elements[7]};

			float mat[16] {mat3(f00).determinant(), mat3(f01).determinant(), mat3(f02).determinant(), mat3(f03).determinant(),
				mat3(f10).determinant(), mat3(f11).determinant(), mat3(f12).determinant(),  mat3(f13).determinant(),
				mat3(f20).determinant(), mat3(f21).determinant(), mat3(f22).determinant(), mat3(f23).determinant(),
				mat3(f30).determinant(), mat3(f31).determinant(), mat3(f32).determinant(), mat3(f33).determinant()};

			// Matrix of cofactors
			mat[1] = -mat[1];
			mat[3] = -mat[3];
			mat[4] = -mat[4];
			mat[6] = -mat[6];
			mat[9] = -mat[9];
			mat[11] = -mat[11];
			mat[12] = -mat[12];
			mat[14] = -mat[14];

			// Adjugate
			mat4 adj = mat4(mat).transpose();

			// Multiply by determinant
			return adj.multiply(this->determinant());
		}

		mat4 mat4::transpose() const {
			vec4 row0 = getRow(0);
			vec4 row1 = getRow(1);
			vec4 row2 = getRow(2);
			vec4 row3 = getRow(3);

			vec4 tranRow0(row0.x, row1.x, row2.x, row3.x);
			vec4 tranRow1(row0.y, row1.y, row2.y, row3.y);
			vec4 tranRow2(row0.z, row1.z, row2.z, row3.z);
			vec4 tranRow3(row0.w, row1.w, row2.w, row3.w);

			return mat4(tranRow0, tranRow1, tranRow2, tranRow3);
		}

		mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far) const {
			mat4 result(1.0f);
			
			result.elements[0] = 2.0f / (right - left);
			result.elements[5] = 2.0f / (top - bottom);
			result.elements[10] = -2.0f / (far - near);

			result.elements[3] = -((right + left) / (right - left));
			result.elements[7] = -((top + bottom) / (top - bottom));
			result.elements[11] = -((far + near) / (far - near));

			/*result.elements[0] = 2.0f / (right - left);
			result.elements[3] = (left + right) / (left - right);
			result.elements[5] = 2.0f / (top - bottom);
			result.elements[7] = (bottom + top) / (bottom - top);
			result.elements[10] = 2.0f / (near - far);
			result.elements[11] = (far + near) / (far - near);*/
			
			return result;
		}

		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far) const {
			mat4 result(1.0f);
			
			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;
			
			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);
			
			result.elements[0] = a;
			result.elements[5] = q;
			result.elements[10] = b;
			result.elements[11] = c;
			result.elements[14] = -1.0f;
			
			return result;
		}

		mat4 mat4::lookAt(const vec3& camera, const vec3& target, const vec3& up) const {
			mat4 result(1.0f);

			vec3 z = vec3(target - camera).normalise();
			vec3 x = vec3(z.cross(up)).normalise();
			vec3 y = x.cross(z);

			result.elements[0] = x.x;
			result.elements[1] = y.x;
			result.elements[2] = z.x;

			result.elements[4] = x.y;
			result.elements[5] = y.y;
			result.elements[6] = z.y;

			result.elements[8] = x.z;
			result.elements[9] = y.z;
			result.elements[10] = z.z;

			result.elements[3] = x.dot(camera);
			result.elements[7] = y.dot(camera);
			result.elements[11] = z.dot(camera);
			
			return result;
		}

		mat4 mat4::translate(const vec3& translation) const {
			mat4 result(1.0f);
			
			result.elements[3] = translation.x;
			result.elements[7] = translation.y;
			result.elements[11] = translation.z;

			return result;
		}

		mat4 mat4::rotate(float radians, const vec3& axis) const {
			mat4 result(1.0f);
			
			float co = cos(radians);
			float si = sin(radians);
			float omc = 1.0f - co;
			
			float x = axis.x;
			float y = axis.y;
			float z = axis.z;
			
			result.elements[0] = co + (x * x) * omc;
			result.elements[1] = x * y * omc - z * si;
			result.elements[2] = x * z * omc + y * si;

			result.elements[4] = y * x * omc + z * si;
			result.elements[5] = co + (y * y) * omc;
			result.elements[6] = y * z * omc - x * si;

			result.elements[8] = z * x * omc - y * si;
			result.elements[9] = z * y * omc + x * si;
			result.elements[10] = co + (z * z) * omc;
			
			return result;
		}

		mat4 mat4::scale(const vec3& scale) const {
			mat4 result(1.0f);
			
			result.elements[0] = scale.x;
			result.elements[5] = scale.y;
			result.elements[10] = scale.z;
			
			return result;
		}

		vec4 mat4::getRow(int index) const {
			int row = index * 4;
			return vec4(elements[row], elements[row + 1], elements[row + 2], elements[row + 3]);
		}

		vec4 mat4::getColumn(int index) const {
			return vec4(elements[0 + index], elements[4 + index], elements[8 + index], elements[12 + index]);
		}

		std::string mat4::toString() const {
			std::stringstream result;
			result << "mat4: (";
			for(int i = 0; i < 15; i++) {
				result << elements[i] << ", ";
			}
			result << elements[15] << ")";
			return result.str();
		}

		std::ostream& operator<<(std::ostream& stream, const mat4& matrix) {
			stream << matrix.toString();
			return stream;
		}
	}
}