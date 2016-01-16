#include "Server.h"
using namespace Watchtower;

void Server::Initialize()
{
	ServerAddress.host = ENET_HOST_ANY;
	//Server

	Running = true;
	const double MS_PER_UPDATE = 1000 / TICKRATE;
	double previous = glfwGetTime();
	double lag = 0.0;
	while (Running)
	{
		double current = glfwGetTime();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// Process Input ()
		while (lag >= MS_PER_UPDATE)
		{
			Update();
			lag -= MS_PER_UPDATE;
		}
	}
}
void Server::Update()
{
}

Server::Server()
{
	if (!glfwInit()) // GLFW failed to initialize.
		throw 1; // TODO: error

	if (enet_initialize()) // enet failed to initialize.
		throw 2; // TODO: error

	Initialize();

	glfwTerminate();
	enet_deinitialize();
}