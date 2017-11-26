#pragma once

#include <GL/glew.h>

#include "Shader.h"

class Uniform {
public:
	Uniform();
	Uniform(GLuint uniformLoc);

	GLuint getUniformLocation();
private:
	GLuint uniformLoc_;

	void setUniformLocation(GLuint uniformLoc);
};