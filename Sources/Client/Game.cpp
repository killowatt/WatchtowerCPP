#include "Game.h"

void Game::Update()
{
}
void Game::Render()
{
}
void Game::Initialize()
{
}

Game::Game(GLFWwindow* window)
{
	Window = window;

	Initialize();
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}