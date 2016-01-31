#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <enet/enet.h>
#include "GameSettings.h"
#include <Server.h>
#include "Graphics/Renderer.h"
#include "Assets/Shaders/BasicColorShader.h"

namespace Watchtower
{
	class Client
	{
	public:
		bool Running;
		static const unsigned short TICK_RATE = 64;

		GLFWwindow* Window;
		Renderer* Renderer;


		BasicColorShader* shaderB;
			float xTest;
			double lastTime;
			double currentTime;
			float deltaTime;

		GameSettings Settings;
		GameMap* CurrentMap;

		ENetHost* ClientHost;
		ENetPeer* ServerPeer;

		void Initialize();
		void Update();
		void Render();

		bool DESTRUCTION = false;
		bool fart = false;
		int xyz = 0;

		bool Connect(std::string address, unsigned short port = Server::DEFAULT_PORT);

		Client();
	};
}