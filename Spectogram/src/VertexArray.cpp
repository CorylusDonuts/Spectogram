#include "VertexArray.h"

#include <iostream>

using namespace std;

VertexArray::VertexArray(unsigned int vertexLength) {
	vl = vertexLength;
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

void VertexArray::AddAttribute(const char num, const unsigned short type) {
	int size = 0;

	switch (type) {
	case GL_FLOAT:
		size = 4;
		break;
	case GL_UNSIGNED_INT:
		size = 4;
		break;
	case GL_INT:
		size = 4;
		break;
	case GL_BYTE:
		size = 1;
		break;
	case GL_SHORT:
		size = 2;
		break;
	}

	offset[index] = stride;
	types[index] = type;
	stride += num * size;

	nums[index] = num;
	currentNum += num;

	if (currentNum == vl) {
		for (int i = 0; i <= index; i++) {
			//cout << i <<" " << nums[i] <<" " << types[i] <<" " << stride <<" " << offset[i] << endl;
			glBindVertexArray(ID);
			glVertexAttribPointer(i, nums[i], types[i], GL_FALSE, stride, (void*)offset[i]);
			glEnableVertexAttribArray(i);
		}
	}

	index++;
}

int VertexArray::GetID() {
	return ID;
}

void VertexArray::Bind() {
	glBindVertexArray(ID);
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}