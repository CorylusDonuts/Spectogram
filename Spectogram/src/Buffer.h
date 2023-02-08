#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

class Buffer {
private:
	unsigned int ID;
	GLenum type = 0;
public:
	Buffer(const void* data, unsigned int size, GLenum bufferType);
	void BindIndex(unsigned int bindingIndex);
	void Bind();
	void Unbind();
	void Delete();
	void Read (void* newdata, unsigned int size, unsigned int index);
	void Write(const void* newdata, unsigned int size, unsigned int index);
	unsigned int GetID();
};
