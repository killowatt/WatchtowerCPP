#pragma once
#include <GLFW/glfw3.h>
#include <enet/enet.h>
#include "ServerParameters.h"

namespace Watchtower
{
	class Server
	{
	public:
		bool Running;
		static const unsigned short TICKRATE = 64;

		ServerParameters Settings;

		ENetHost* ServerHost;
		ENetAddress ServerAddress;

		void Initialize();
		void Update();

		Server();
	};
}