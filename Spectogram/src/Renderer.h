#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

class Renderer {
private:

public:
	Renderer();
	void Draw(VertexArray& vertexArray, Shader& shader, Buffer& indexBuffer);
	void Clear();
};