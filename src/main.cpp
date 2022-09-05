#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include"Renderer/Shaders/ShaderProgram.h"
#include"Renderer/Drawable/Sprite.h"
#include"Core/Resources/ResourceManager.h"
#include"glm/vec2.hpp"
#include"glm/mat4x4.hpp"
#include"glm/gtc/matrix_transform.hpp"

glm::ivec2 w_size(640, 480);

void glfwWindowSizeCallback(GLFWwindow* win, int w, int h) {
	w_size.x = w;
	w_size.y = h;
	glViewport(0, 0, w_size.x, w_size.y);
}
void glfwKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, GL_TRUE);
	}
	if (key == GLFW_KEY_RIGHT) {
	}
	if (key == GLFW_KEY_LEFT) {
	}
	if (key == GLFW_KEY_UP) {
	}
	if (key == GLFW_KEY_DOWN) {
	}
}
int main(int argc, char** argv)
{

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(w_size.x, w_size.y, "Hello World", NULL, NULL);
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

	glClearColor(0.f, 0.f, 0, 0);
	{
		ResourceManager resourceManager(argv[0]);

		auto shaderProgram = resourceManager.LoadShader("shader", "res/shaders/standart.vsh", "res/shaders/standart.fsh");

		auto tex = resourceManager.LoadTexture("texture", "res/textures/test2.png");

		auto sprite = resourceManager.LoadSprite("sprite", "texture", "shader", glm::vec3(0.f, 0.f, 0.f));
		Core::Transform trans = sprite->GetTransform();
		trans.SetPosition2D(glm::vec2(100.f,100.f));
		trans.SetRotation2D(45.f);
		trans.Scale(glm::vec2(.1f, .1f));
		sprite->SetTransform(trans);
		/* Loop until the user closes the window */
		shaderProgram->Use();
		shaderProgram->SetSampler("sampler0", 0);


		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(w_size.x), 0.f, static_cast<float>(w_size.y), -100.f, 100.f);
		shaderProgram->SetMatrix4("projection_mat", projectionMatrix);

		while (!glfwWindowShouldClose(window)){
			glClear(GL_COLOR_BUFFER_BIT);

			sprite->Draw();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}