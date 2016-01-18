#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <enet/enet.h>
#include "GameSettings.h"
#include <Server.h>

namespace Watchtower
{
	class Client
	{
	public:
		bool Running;
		static const unsigned short TICK_RATE = 64;

		GLFWwindow* Window;
		GameSettings Settings;

		ENetHost* ClientHost;
		ENetPeer* ServerPeer;

		void Initialize();
		void Update();
		void Render();

		bool Connect(std::string address, unsigned short port = Server::DEFAULT_PORT);

		Client();
	};
}