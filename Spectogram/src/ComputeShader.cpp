#include "ComputeShader.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


ComputeShader::ComputeShader(const char* computePath) {
	// compute shader
	std::string computeCode;
	std::ifstream cShaderFile;

	cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		cShaderFile.open(computePath);
		std::stringstream cShaderStream;
		// read file’s buffer contents into streams
		cShaderStream << cShaderFile.rdbuf();
		// close file handlers
		cShaderFile.close();
		// convert stream into string
		computeCode = cShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::COMPUTE_SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* cShaderCode = computeCode.c_str();


	ID = glCreateProgram();
	if (0 == ID)
		std::cout << "failed to create compute program" << std::endl;
	unsigned int csProgram = Compile(GL_COMPUTE_SHADER, cShaderCode);
	glAttachShader(ID, csProgram);
	glLinkProgram(ID);

	glValidateProgram(ID);
	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		glGetProgramInfoLog(ID, 512, NULL, &infoLog[0]);
		std::cout << "Compute Link error" << std::endl;
		std::cout << infoLog << std::endl;
	}

	glDeleteShader(csProgram);
}

unsigned int ComputeShader::Compile(unsigned int type, const char* source) {
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

void ComputeShader::Dispatch(unsigned int x, unsigned int y, unsigned int z)
{
	Bind();
	glDispatchCompute(x, y, z);
}

void ComputeShader::Bind() {
	glUseProgram(ID);
}

void ComputeShader::Unbind() {
	glUseProgram(0);
}