#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OldClient.h"

#include <Utilities.h>
#include <ServerParameters.h>

int main() 
{ // TODO: move initialization to their subsystems..
	ServerParameters::Load();

	if (!glfwInit())
		return 1; // GLFW failed to initialize.
	 
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Watchtower", nullptr, nullptr); // TODO: load settings

	if (window)
	{
		glfwMakeContextCurrent(window);
		glewExperimental = true;
		if (glewInit() == GLEW_OK)
		{
			Clientx Clientx(window);
		}
	}

	glfwTerminate();
	return 0;
}