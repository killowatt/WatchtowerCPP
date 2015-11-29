#include "Game.h"

// temp
#include "Graphics\VertexBuffer.h"
#include <vector>

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

	Graphics::VertexBuffer x;
	x.SetBufferData(std::vector<float>(6, 1), 3, Graphics::MemoryHint::Static);
	Graphics::VertexBuffer y = x;

	Initialize();
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}