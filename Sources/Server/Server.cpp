#include "Server.h"
#include <ByteStream.h>

#include <iostream>
#include "Network/Packets.h"

using namespace Watchtower;

void Server::Initialize()
{
	if (Settings.ServerIP == "")
		ServerAddress.host = ENET_HOST_ANY;
	else
		enet_address_set_host(&ServerAddress, Settings.ServerIP.c_str());
	ServerAddress.port = Settings.Port;

	ServerHost = enet_host_create(&ServerAddress, Settings.MaxPlayers, 2, 0, 0);

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
				std::cout << "Received player data. Name " << data.PlayerName << "\n";

				//ByteStream stream;
				//stream.Write((char)PacketType::ClientDataReceived);
				//ENetPacket* packet = enet_packet_create(stream.GetData(), stream.GetSize(),
				//	ENET_PACKET_FLAG_RELIABLE);
				//enet_peer_send(event.peer, 0, packet);
				//enet_host_flush(ServerHost);
			}
		}
		else if (event.type == ENET_EVENT_TYPE_DISCONNECT)
			std::cout << "Client disconnected. " << event.peer->address.host;
		else {}
	}
}

Server::Server()
{
	Players.reserve(Settings.MaxPlayers);
	PlayerCount = 0;

	Settings = ServerParameters::Load();

	if (!glfwInit()) // GLFW failed to initialize.
		throw 1; // TODO: error

	if (enet_initialize()) // enet failed to initialize.
		throw 2; // TODO: error

	Initialize();

	glfwTerminate();
	enet_deinitialize();
}