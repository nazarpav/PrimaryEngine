#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include"Renderer/Shaders/ShaderProgram.h"
#include"Core/Resources/ResourceManager.h"
struct FDot {
	float x;
	float y;
};
struct IDot {
	int x;
	int y;
};
IDot w_size;

GLfloat points[] = {
	0.0f,0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	-0.5f,-0.5f,0.0f
};

GLfloat colors[] = {
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f
};

void glfwWindowSizeCallback(GLFWwindow* win, int w, int h) {
	w_size.x = w;
	w_size.y = h;
	glViewport(0, 0, w_size.x, w_size.y);
}
void glfwKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, GL_TRUE);
	}
}
int main(int argc, char** argv)
{

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
	glfwSetKeyCallback(window, glfwKeyCallback);

	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(0, 1, 0, 1);
	{
		ResourceManager resourceManager(argv[0]);

		auto shaderProgram = resourceManager.LoadShader("StandartShader", "res/shaders/standart.vsh", "res/shaders/standart.fsh");

		if (shaderProgram == false) {
			std::cerr << "Can`t create shader program!" << std::endl;
			return -1;
		}

		GLuint points_vbo = 0;
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			shaderProgram->use();
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}