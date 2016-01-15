#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <enet/enet.h>
#include "GameSettings.h"

namespace Watchtower
{
	class Client
	{
	public:
		bool Running;
		static const unsigned short TICKRATE = 64;

		GLFWwindow* Window;
		GameSettings Settings;

		void Initialize();
		void Update();
		void Render();

		Client();
	};
}