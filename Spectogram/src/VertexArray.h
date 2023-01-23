#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

class VertexArray {
private:
	unsigned int index = 0;
	unsigned int ID;
	unsigned int stride = 0;
	unsigned int vl = 0;
	unsigned int currentNum = 0;

	GLenum types[64];
	unsigned short nums[64];
	unsigned short offset[64];
public:
	VertexArray(unsigned int vertexLength);
	void AddAttribute(const char num, const unsigned short type);

	int GetID();

	void Bind();
	void Unbind();
};