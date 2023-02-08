#pragma once


class ComputeShader {
private:
	unsigned int ID;
	unsigned int Compile(unsigned int type, const char* source);
public:
	ComputeShader(const char* computePath);
	void Dispatch(unsigned int x, unsigned int y, unsigned int z);
	void Bind();
	void Unbind();
};
