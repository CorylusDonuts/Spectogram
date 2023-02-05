#include "Fractal.h"



#include <iostream>

Fractal::Fractal(GLFWwindow* window, Renderer& renderer) 
	: shader(R"r(.\res\shaders\Vertex.shader)r", R"r(.\res\shaders\FractalFragment.shader)r"), 
	window(window), 
	renderer(renderer), 
	va(2), 
	buffer(positions, sizeof(positions), VBO), 
	indexBuffer(indices, sizeof(indices), EBO)
{
	va.Bind();
	va.AddAttribute(2, GL_FLOAT);
}
void Fractal::Update(unsigned int& res_x, unsigned int& res_y) {
	renderer.Clear();
	shader.Bind();
	shader.setUint("dimx", res_x);
	shader.setUint("dimy", res_y);

	renderer.Draw(va, shader, indexBuffer);
}

void Fractal::ProcessInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {y += 0.025 * scale;
		shader.set2D("translate", x, y);}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {y -= 0.025 * scale;
		shader.set2D("translate", x, y);}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {x += 0.025 * scale;
		shader.set2D("translate", x, y);}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {x -= 0.025 * scale;
		shader.set2D("translate", x, y);}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {scale *= 1.025;
		shader.set1D("scale", scale);}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {scale *= 0.975;
		shader.set1D("scale", scale);}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {offsetr += 0.05f;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {offsetg += 0.05f;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {offsetb += 0.05f;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {offsetr -= 0.05f;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {offsetg -= 0.05f;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {offsetb -= 0.05f;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {maxIter = std::clamp(int(maxIter * 1.025), 40, 1500);
		shader.setInt("maxIter", maxIter);}
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {maxIter = std::clamp(int(maxIter / 1.025), 40, 1500);
		shader.setInt("maxIter", maxIter);}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {distfac = std::clamp(distfac + float(0.001), float(0.0), float(1.0));
		shader.set1F("distfac", distfac);}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {distfac = std::clamp(distfac - float(0.001), float(0.0), float(1.0));
		shader.set1F("distfac", distfac);}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {shift += 0.1f;
		shader.set1F("shift", shift);}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {shift -= 0.1f;
		shader.set1F("shift", shift);}
}