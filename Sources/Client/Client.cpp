#include "Client.h"
using namespace Watchtower;

void Client::Initialize()
{

	// Start the game loop.
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
		Render();
	}
}

void Client::Update()
{
}
void Client::Render()
{
}

Client::Client()
{
	Settings = Settings::Load();

	if (!glfwInit()) // GLFW failed to initialize.
		throw 1; // TODO: error

	if (enet_initialize()) // enet failed to initialize.
		throw 2; // TODO: error

	// Set up window hints based on settings.
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_VISIBLE, false);
	if (Settings.WindowType == WindowType::BorderlessWindow)
		glfwWindowHint(GLFW_DECORATED, false);

	Window = glfwCreateWindow(Settings.WindowWidth, Settings.WindowHeight,
		"Watchtower", nullptr, nullptr);

	// Do not continue if the window failed to create.
	if (Window)
	{
		glfwMakeContextCurrent(Window);
		glewExperimental = true;
		if (glewInit() == GLEW_OK)
			Initialize();
	}
	// Terminate GLFW after we've finished.
	glfwTerminate();
}
Client::~Client()
{
}