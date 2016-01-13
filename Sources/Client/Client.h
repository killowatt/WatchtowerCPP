#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <enet/enet.h>
#include "Settings.h"

namespace Watchtower
{
	class Client
	{
	public:
		bool Running;
		static const unsigned short TICKRATE = 64;

		GLFWwindow* Window;
		Settings Settings;

		void Initialize();
		void Update();
		void Render();

		Client();
		~Client();
	};
}