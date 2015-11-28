#pragma once
#include <GLFW/glfw3.h>

class Game
{
public:
	GLFWwindow* Window;

	void Initialize();
	void Update();
	void Render();

	bool Running;

	Game(GLFWwindow* window);
};