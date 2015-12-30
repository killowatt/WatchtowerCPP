#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "MemoryStream.h"

int main() 
{
	MemoryStream m;
	//m.Write((unsigned char)50);
	//m.Write((uint64_t)18446744073709551615);
	m.Write(3.14159f);
	//std::cout << "NUM IS " << (int)m.ReadByte() << "\n";
	//std::cout << "LONG IS " << (uint64_t)m.ReadUnsignedLong() << "\n";
	std::cout << "PI IS " << m.ReadFloat() << "\n";

	getchar();
	
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