#include "Server.h"
#include <ByteStream.h>


#include "Network/Packet.h"

using namespace Watchtower;

void Server::Initialize()
{
	if (Settings.ServerIP == "")
		ServerAddress.host = ENET_HOST_ANY;
	else
		enet_address_set_host(&ServerAddress, Settings.ServerIP.c_str());
	ServerAddress.port = Settings.Port;

	if (ServerHost == nullptr)
		return; // TODO: error!!

	// Start server loop.
	Running = true;
	const double MS_PER_UPDATE = 1000 / TICKRATE;
	double previous = glfwGetTime();
	double lag = 0.0;
	while (Running)
	{
		double current = glfwGetTime();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		// Process Input ()
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
	while (enet_host_service(ServerHost, &event, 100))
	{
		if (event.type == ENET_EVENT_TYPE_CONNECT)
			printf("Client connected.\n", event.peer->address.host);
			
		else if (event.type == ENET_EVENT_TYPE_RECEIVE)
		{
			ByteStream reader(event.packet->data, event.packet->dataLength);
			unsigned char packetType = reader.ReadChar();
			if (packetType == PacketType::ClientData)
			{
				printf("Received packet CLIENTDATA");
			}
		}
		else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {}
		else {}
	}
}

Server::Server()
{
	Settings = ServerParameters::Load();

	if (!glfwInit()) // GLFW failed to initialize.
		throw 1; // TODO: error

	if (enet_initialize()) // enet failed to initialize.
		throw 2; // TODO: error

	Initialize();

	glfwTerminate();
	enet_deinitialize();
}