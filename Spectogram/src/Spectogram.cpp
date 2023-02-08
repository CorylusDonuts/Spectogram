#include "Spectogram.h"



Spectogram::Spectogram(GLFWwindow* window, Renderer& renderer, unsigned int samplePoints)
	: cs(R"r(.\res\shaders\Compute.shader)r"),
	window(window),
	renderer(renderer),
	sampleNum(samplePoints)
{

}

void Spectogram::Update(unsigned int& res_x, unsigned int& res_y) {

}
