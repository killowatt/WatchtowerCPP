#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Client.h"

#include "Entity.h"
#include "EntityManager.h"


class ent : public Entity
{
public:
	int x;
	std::string y;
	ent() : Entity(0)
	{
		x = 55;
		y = std::string("hello!");
	}
};
int main() 
{ // TODO: move initialization to their subsystems..


	EntityManager x;
	ent* enty = new ent();
	x.AddEntity(enty);

	std::cout << (ent*)(x.entities[0].get())->

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