#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "ComputeShader.h"
#include <algorithm>



class Spectogram {
private:
	GLFWwindow* window;
	Renderer renderer;
	unsigned int sampleNum;

public:
	ComputeShader cs;



	Spectogram(GLFWwindow* window, Renderer& renderer, unsigned int samplePoints);
	void Update(unsigned int& res_x, unsigned int& res_y);
};