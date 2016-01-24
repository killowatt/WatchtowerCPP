#include "Server.h"
#include <ByteStream.h>

#include <iostream>
#include "Network/Packets.h"

#include "lodepng.h"

using namespace Watchtower;

void SetupChunks(GameMap* world) // TODO: remove, its temp!!
{
	// Here we load in a test heightmap just for kicks okay
	std::vector<unsigned char> image;
	unsigned int width, height;
	lodepng::decode(image, width, height, "terrain_128_height.png");

	unsigned char r[256 * 256];
	int stride = 1024; // 256 pixels wide * 4 channels
	int count = 0;

	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			r[count++] = image[(row * stride) + (column * 4)];
		}
	}

	for (int cx = 0; cx < 16; cx++)
	{
		for (int cy = 0; cy < 16; cy++)
		{
			for (int bx = 0; bx < 16; bx++)
			{
				for (int by = 0; by < 16; by++)
				{
					for (int bz = 0; bz <
						r[(width * (bx + (cx * 16))) + (by + (cy * 16))] / 1; bz++)
					{
						world->GetChunk(cx, cy).GetBlock(bx, bz, by).Active = true;
						world->GetChunk(cx, cy).GetBlock(bx, bz, by).Color = 
							Color(bz * 2, 40, 94);
					}
				}
			}
		}
	}
}



void Server::Initialize()
{
	if (Settings.ServerIP == "")
		ServerAddress.host = ENET_HOST_ANY;
	else
		enet_address_set_host(&ServerAddress, Settings.ServerIP.c_str());
	ServerAddress.port = Settings.Port;

	ServerHost = enet_host_create(&ServerAddress, Settings.MaxPlayers, 2, 0, 0);


	// TEMP -- We temporarily create map data from heightmap
	GameMap* SAVE = new GameMap(16, 16);
	SetupChunks(SAVE);
	SAVE->Save("TestMap.vxlm");
	delete SAVE;

	CurrentMap = GameMap::Load("TestMap.vxlm");
	// TEMP


	if (ServerHost == nullptr)
		return; // TODO: error!!

	// Start server loop.
	Running = true;
	const double MS_PER_UPDATE = 1.0 / TICK_RATE;
	double previous = glfwGetTime();
	double lag = 0.0;
	while (Running)
	{
		double current = glfwGetTime();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		while (lag >= MS_PER_UPDATE)
		{
			Update();
			lag -= MS_PER_UPDATE;
		}
	}
}
void Server::Update()
{
	ENetEvent event;
	while (enet_host_service(ServerHost, &event, 1000) > 0)
	{
		if (event.type == ENET_EVENT_TYPE_CONNECT)
			std::cout << "Client connected. " << event.peer->address.host << "\n";
		else if (event.type == ENET_EVENT_TYPE_RECEIVE)
		{
			ByteStream reader(event.packet->data, event.packet->dataLength);
			unsigned char packetType = reader.ReadChar();
			if (packetType == PacketType::ClientData)
			{
				ClientData data = ClientData::Read(reader);
				Players.push_back(Player(data.PlayerName));
				event.peer->data = &Players.back();
				std::cout << "Received player data. Name " << data.PlayerName << "\n";
				SendMap(event.peer);
			}

		}
		else if (event.type == ENET_EVENT_TYPE_DISCONNECT)
			std::cout << "Client disconnected. " << event.peer->address.host;
		else {}
	}
}

void Server::SendMap(ENetPeer* peer)
{
	unsigned int totalChunks = CurrentMap->GetWidth() * CurrentMap->GetHeight();
	MapInfo mapInfo("Watchtower Test Map", totalChunks);
	ENetPacket* packet = mapInfo.ToStream().ToPacket();
	enet_peer_send(peer, 0, packet);
	enet_host_flush(ServerHost);
	enet_packet_destroy(packet);

	for (int i = 0; i < CurrentMap->GetTotalChunks(); i++)
	{

	}
}

Server::Server()
{
	Players.reserve(Settings.MaxPlayers);
	PlayerCount = 0;
	
	Settings = ServerParameters::Load();

	// Pointers
	ServerHost = nullptr;
	CurrentMap = nullptr;

	if (!glfwInit()) // GLFW failed to initialize.
		throw 1; // TODO: error

	if (enet_initialize()) // enet failed to initialize.
		throw 2; // TODO: error

	Initialize();

	glfwTerminate();
	enet_deinitialize();
}