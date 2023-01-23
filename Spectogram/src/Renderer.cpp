#include "Renderer.h"
#include <iostream>


Renderer::Renderer() {
	
}

void Renderer::Draw(VertexArray& vertexArray, Shader& shader, Buffer& indexBuffer) {
	shader.Bind();
	vertexArray.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::Clear() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}