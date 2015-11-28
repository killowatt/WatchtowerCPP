#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "Game.h"

int main() 
{
	if (!glfwInit())
		return 1; // GLFW failed to initialize.
	 
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Watchtower", nullptr, nullptr); // TODO: load settings

	if (window)
	{
		glfwMakeContextCurrent(window);
		glewExperimental = true;
		if (glewInit() == GLEW_OK)
		{
			Game game = Game(window);
		}
	}

	glfwTerminate();
	return 0;
}