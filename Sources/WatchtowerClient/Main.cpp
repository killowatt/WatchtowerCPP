#include <iostream>
#include <GLFW\glfw3.h>

int main(void)
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Watchtower", nullptr, nullptr);
	glfwMakeContextCurrent(window);


	glClearColor(25.0f / 255, 25.0f / 255, 25.0f / 255, 1.0f);
	while (glfwWindowShouldClose(window) != 1)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}