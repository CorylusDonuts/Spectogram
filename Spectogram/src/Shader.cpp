#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file’s buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();


	ID = glCreateProgram();
	if (0 == ID)
		std::cout << "failed to create program" << std::endl;
	unsigned int vsProgram = Compile(GL_VERTEX_SHADER, vShaderCode);
	unsigned int fsProgram = Compile(GL_FRAGMENT_SHADER, fShaderCode);

	glAttachShader(ID, vsProgram);
	glAttachShader(ID, fsProgram);
	glLinkProgram(ID);

	glValidateProgram(ID);
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		glGetProgramInfoLog(ID, 512, NULL, &infoLog[0]);
		std::cout << "Link error" << std::endl;
		std::cout << infoLog << std::endl;
	}

	glDeleteShader(vsProgram);
	glDeleteShader(fsProgram);
}

unsigned int Shader::Compile(unsigned int type, const char* source) {
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to Compile shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

void Shader::setUint(const char* name, unsigned int& value) {
	glUniform1ui(glGetUniformLocation(ID, name), value);
}

void Shader::setInt(const char* name, int& value) {
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::set4F(const char* name, float& val1, float& val2, float& val3, float& val4) {
	glUniform4f(glGetUniformLocation(ID, name), val1, val2, val3, val4);
}
void Shader::set3F(const char* name, float& val1, float& val2, float& val3) {
	glUniform3f(glGetUniformLocation(ID, name), val1, val2, val3);
}
void Shader::set2F(const char* name, float& val1, float& val2) {
	glUniform2f(glGetUniformLocation(ID, name), val1, val2);
}
void Shader::set1F(const char* name, float& val1) {
	glUniform1f(glGetUniformLocation(ID, name), val1);
}




void Shader::Bind() {
	glUseProgram(ID);
}

void Shader::Unbind() {
	glUseProgram(0);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}