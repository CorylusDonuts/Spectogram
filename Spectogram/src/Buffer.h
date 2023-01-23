#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

class Buffer {
private:
	unsigned int ID;
	GLenum type = 0;
public:
	Buffer(const void* data, unsigned int size, GLenum bufferType);

	void Bind();
	void Unbind();
	void Delete();
	unsigned int GetID();
};
