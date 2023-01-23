#include "Buffer.h"

Buffer::Buffer(const void* data, unsigned int size, GLenum bufferType) {

	type = bufferType;
	glGenBuffers(1, &ID);
	glBindBuffer(type, ID);
	glBufferData(type, size, data, GL_STATIC_DRAW);
}

void Buffer::Bind() {
	glBindBuffer(type, ID);
}
void Buffer::Unbind() {
	glBindBuffer(type, 0);
}
void Buffer::Delete() {
	glDeleteBuffers(1, &ID);
}

unsigned int Buffer::GetID() {
	return ID;
}