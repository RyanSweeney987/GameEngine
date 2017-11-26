#include "Shader.h"

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
	std::string vertexCode = loadShaderFiles(vertexPath);
	std::string fragmentCode = loadShaderFiles(fragmentPath);

	GLuint vertShader = createShader(GL_VERTEX_SHADER, vertexCode.c_str());
	GLuint fragShader = createShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

	createProgram(vertShader, fragShader);
}

//Shader::Shader(const Shader& data) {
//	program_ = data.program_;
//}

//Shader::Shader(Shader&& data) {
//	program_ = data.program_;
//
//	data.program_ = 0;
//}

Shader::~Shader() {
	glDeleteProgram(program_);
	program_ = 0;

	std::cout << "Destroying shader program" << std::endl;
}

void Shader::useProgram() {
	glUseProgram(program_);
}

GLuint& Shader::getProgram() {
	return program_;
}

GLuint Shader::getUniformLocation(const char * uniformName) {
	return glGetUniformLocation(program_, uniformName);
}

std::string Shader::loadShaderFiles(const GLchar* path) {
	std::cout << "Loading shader: " << path << std::endl;

	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::badbit);

	try {
		shaderFile.open(path);

		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderCode = shaderStream.str();
	} catch(std::ifstream::failure e) {
		std::cout << "Error loading shader: File unsuccessfully read" << std::endl;
	}

	return shaderCode;
}

GLuint Shader::createShader(GLenum shaderType, const GLchar* source) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error: Shader compilation failed\n" << infoLog << std::endl;

		return 0;
	}

	return shader;
}

void Shader::createProgram(GLuint& vertexShader, GLuint& fragmentShader) {
	program_ = glCreateProgram();
	glAttachShader(program_, vertexShader);
	glAttachShader(program_, fragmentShader);
	glLinkProgram(program_);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(program_, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(program_, 512, NULL, infoLog);
		std::cout << "Error: Shader program compilation failed\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
