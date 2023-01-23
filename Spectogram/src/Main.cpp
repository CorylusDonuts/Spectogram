#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <filesystem>
#include <string>
#include <math.h>

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


void processInput(GLFWwindow* window, Shader& shader, float& x, float& y, float& scale)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	//if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {y += 0.025 * scale;
	//	shader.set2F("translate", x, y);}
	//if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {y -= 0.025 * scale;
	//	shader.set2F("translate", x, y);}
	//if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {x += 0.025 * scale;
	//	shader.set2F("translate", x, y);}
	//if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {x -= 0.025 * scale;
	//	shader.set2F("translate", x, y);}
	//if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){scale *= 1.025;
	//	shader.set1F("scale", scale);}
	//if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){scale *= 0.975;
	//	shader.set1F("scale", scale);}

}

int main()
{
	const int x = 1000;
	const int y = 1000;

	

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
		  0.8,  0.8,
		 -0.8,  0.8,
		 -0.8, -0.8,
		  0.8, -0.8,
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
	
	//VertexArray va1(2);
	//Buffer buffer(positions1, sizeof(positions1), VBO);
	//Buffer indexBuffer(indices, sizeof(indices), EBO);
	//va1.AddAttribute(2, GL_FLOAT);
	
	

	float scale = 1;
	float posx = 0;
	float posy = 0;

	const double frameTime = 125.0/18.0;
	double time = glfwGetTime() * 1000;
	
	
	while (!glfwWindowShouldClose(window))
	{
		//cout << time << endl;
		processInput(window, shader, posx, posy, scale);
		unsigned int dim = x;
		

		renderer.Clear();




		//shader.setUint("dim", dim);
		//shader.Bind();
		//renderer.Draw(va1, shader, indexBuffer);
		

		glfwSwapBuffers(window);
		glfwPollEvents();

		
		glfwSetTime(0.0);
	}
	shader.Delete();

	glfwTerminate();
	return 0;
}