#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <filesystem>
#include <string>
#include <math.h>
#include <algorithm>

#include "Renderer.h"
#include "Shader.h"
#include "ComputeShader.h"
#include "Buffer.h"
#include "VertexArray.h"

#define VBO GL_ARRAY_BUFFER
#define EBO GL_ELEMENT_ARRAY_BUFFER
#define SSBO GL_SHADER_STORAGE_BUFFER


using namespace std;

#define call(x) x;\
    if (error) __debugbreak();

bool error = false;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void* userParam) {
	error = true;
	std::cout << "[OpenGL Error](" << type << ") " << message << std::endl;
}


void processInput(GLFWwindow* window, Shader& shader, double& x, double& y, double& scale, float&offsetr, float& offsetg, float& offsetb, int& maxIter, float& distfac, float& shift)
{
	
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
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){scale *= 1.025;
		shader.set1D("scale", scale);}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){scale *= 0.975;
		shader.set1D("scale", scale);}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {offsetr += 0.05;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}		 
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {offsetg += 0.05;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}		 
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {offsetb += 0.05;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}		 
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {offsetr -= 0.05;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}		 
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {offsetg -= 0.05;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}		 
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {offsetb -= 0.05;
		shader.set3F("coloffset", offsetr, offsetg, offsetb);}
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {maxIter = std::clamp(int(maxIter * 1.025), 40, 1500);
		shader.setInt("maxIter", maxIter);}
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {maxIter = std::clamp(int(maxIter / 1.025), 40, 1500);
		shader.setInt("maxIter", maxIter);}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {distfac = std::clamp(distfac + float(0.001), float(0.0), float(1.0));
		shader.set1F("distfac", distfac);}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {distfac = std::clamp(distfac - float(0.001), float(0.0), float(1.0));
		shader.set1F("distfac", distfac);}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {shift += 0.1;
		shader.set1F("shift", shift);}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {shift -= 0.1;
		shader.set1F("shift", shift);}
}

int main()
{
	const int x = 1920/2;
	const int y = 1080/2;

	

	glfwInit();
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(x, y, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	glViewport(0, 0, x, y);


	Renderer renderer;
	



	const float positions1[] = {
		  1.0,  1.0,
		 -1.0,  1.0,
		 -1.0, -1.0,
		  1.0, -1.0,
	};
	const unsigned int indices[] = {
		0, 3, 2,
		2, 1, 0
	};

	//sample rate 1 / 10 s
	float signals[64]{0};
	float freq[64]{0};

	const float FREQ1 = 5;
	const float FREQ2 = 12;
	
	for (int i = 0; i < 64; i++) {
		signals[i] = sinf(2 * 3.14159265359 * FREQ1 * i / 64) + sinf(2 * 3.14159265359 * FREQ2 * i / 64);
	}

	

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	Shader shader(R"r(.\res\shaders\Vertex.shader)r", R"r(.\res\shaders\FractalFragment.shader)r");
	
	
	ComputeShader computeShader(R"r(.\res\shaders\Compute.shader)r");

	
	Buffer frequency(freq, sizeof(freq), SSBO);
	glBindBufferBase(SSBO, 4, frequency.GetID());
	Buffer signal(signals, sizeof(signals), SSBO);
	glBindBufferBase(SSBO, 3, signal.GetID());
	
	computeShader.Bind();
	glDispatchCompute(64, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	float max = 0;
	int maxi = 0;
	float data[64]{0};
	frequency.Bind();
	glGetBufferSubData(SSBO, 0, 64 * 4, data);
	for (int i = 0; i < 64; i++) {
		std::cout << data[i] << std::endl;
		if (data[i] > max) {
			max = data[i];
			maxi = i;
		}
	}
	std::cout << 50.0*maxi/64.0 << std::endl;

	int count;
	glGetIntegerv(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, &count);
	cout << count << endl;
	
	//Part of the fractal shader
	VertexArray va1(2);
	Buffer buffer(positions1, sizeof(positions1), VBO);
	Buffer indexBuffer(indices, sizeof(indices), EBO);
	va1.AddAttribute(2, GL_FLOAT);
	
	

	double scale = 1;
	double posx = 0;
	double posy = 0;
	float offsetr = 0.0;
	float offsetg = 0.0;
	float offsetb = 0.0;
	int maxIter = 600;
	float distfac = 0.3;
	float shift = 2.0;

	const double frameTime = 125.0/18.0;
	double time = glfwGetTime() * 1000;
	
	
	while (!glfwWindowShouldClose(window))
	{
		//cout << time << endl;
		processInput(window, shader, posx, posy, scale, offsetr, offsetg, offsetb, maxIter, distfac, shift);
		unsigned int dimx = x;
		unsigned int dimy = y;

		renderer.Clear();



		//part of the fractal shader
		shader.setUint("dimx", dimx);
		shader.setUint("dimy", dimy);
		shader.Bind();
		renderer.Draw(va1, shader, indexBuffer);
		

		glfwSwapBuffers(window);
		glfwPollEvents();

		
		glfwSetTime(0.0);
	}
	shader.Delete();

	glfwTerminate();
	return 0;
}