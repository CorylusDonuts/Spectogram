#pragma once
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include <algorithm>

#define VBO GL_ARRAY_BUFFER
#define EBO GL_ELEMENT_ARRAY_BUFFER
#define SSBO GL_SHADER_STORAGE_BUFFER

class Fractal {
private:
	double scale = 1.0;
	double x = 0.0;
	double y = 0.0;
	float offsetr = 0.0f;
	float offsetg = 0.0f;
	float offsetb = 0.0f;
	int maxIter = 600;
	float distfac = 0.3f;
	float shift = 2.0f;
	GLFWwindow* window;
	Renderer renderer;
	const float positions[8] = {
		  1.0,  1.0,
		 -1.0,  1.0,
		 -1.0, -1.0,
		  1.0, -1.0,
	};
	const unsigned int indices[6] = {
		0, 3, 2,
		2, 1, 0
	};
public:
	Shader shader;
	VertexArray va;
	Buffer buffer;
	Buffer indexBuffer;

	Fractal(GLFWwindow* window, Renderer& renderer);
	void Update(unsigned int& res_x, unsigned int& res_y);
	void ProcessInput();
};