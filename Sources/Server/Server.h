#pragma once
#include <GLFW/glfw3.h>
#include <enet/enet.h>
#include <vector>
#include <GameMap.h>
#include "ServerParameters.h"
#include "Player.h"

namespace Watchtower
{
	class Server
	{
	public:
		bool Running;
		static const unsigned short DEFAULT_PORT = 22737;
		static const unsigned short TICK_RATE = 64;

		ENetHost* ServerHost;
		ENetAddress ServerAddress;
		
		std::vector<Player> Players;
		unsigned short PlayerCount;

		GameMap* CurrentMap;
		ServerParameters Settings;

		void Initialize();
		void Update();

		void ChangeMap(); // TODO:
		void SendMap(ENetPeer* peer);

		Server();
	};
}