#pragma once
#include <GLFW/glfw3.h>
#include <enet/enet.h>

namespace Watchtower
{
	class Server
	{
	public:
		bool Running;
		static const unsigned short TICKRATE = 64;

		ENetHost* ServerHost;
		ENetAddress ServerAddress;

		void Initialize();
		void Update();

		Server();
	};
}