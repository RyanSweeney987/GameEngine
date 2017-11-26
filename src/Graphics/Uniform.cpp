#include "Uniform.h"

Uniform::Uniform() {
}

Uniform::Uniform(GLuint uniformLoc) {
	setUniformLocation(uniformLoc);
}

GLuint Uniform::getUniformLocation() {
	return uniformLoc_;
}

void Uniform::setUniformLocation(GLuint uniformLoc) {
	uniformLoc_ = uniformLoc;
}
