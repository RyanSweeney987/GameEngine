#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "Uniform.h"

class Shader {
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	//Shader(const Shader& data);
	//Shader(Shader&& data);

	~Shader();

	void useProgram();
	GLuint& getProgram();

	GLuint getUniformLocation(const char* uniformName);
private:
	GLuint program_;

	std::string loadShaderFiles(const GLchar* path);
	GLuint createShader(GLenum shaderType, const GLchar* source);
	void createProgram(GLuint& vertexShader, GLuint& fragmentShader);
};