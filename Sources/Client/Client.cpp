#include "Client.h"
#include <iostream>
#include <ByteStream.h>
#include <Network/Packets.h>
using namespace Watchtower;

void Client::Initialize()
{
	// Set up OpenGL stuff.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(20 / 255.0f, 20 / 255.0f, 20 / 255.0f, 1.0f);

	printf("Press enter when ready to connect. \n");
	getchar();
	Connect("127.0.0.1");

	// Start the game loop.
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

		// Process Input ()
		while (lag >= MS_PER_UPDATE)
		{
			Update();
			lag -= MS_PER_UPDATE;
		}
		Render();
	}
}

void Client::Update()
{
	ENetEvent event;
	while (enet_host_service(ClientHost, &event, 5000) > 0)
	{
		if (event.type == ENET_EVENT_TYPE_RECEIVE)
		{
			ByteStream reader(event.packet->data, event.packet->dataLength);
			unsigned char packetType = reader.ReadChar();
			if (packetType == PacketType::ClientDataReceived)
			{
				printf("Client data received by server.\n");
			}
			if (packetType == PacketType::MapInfo)
			{
				printf("Received map info. \n");
				MapInfo mapInfo = MapInfo::Read(reader);
				std::cout << "Map Name: " << mapInfo.Name << "\n";
				std::cout << "Total Chunks: " << mapInfo.TotalChunks << "\n";
			}
		}
		else if (event.type == ENET_EVENT_TYPE_DISCONNECT)
		{
			printf("Disconnected.");
		}
	}
}
void Client::Render()
{
}

bool Client::Connect(std::string address, unsigned short port) // TODO: make errors PLEASE
{
	ClientHost = enet_host_create(nullptr, 1, 2, 0, 0);
	if (!ClientHost) throw 2626; // TODO: something bad happened!

	ENetAddress netAddress;
	ENetEvent event;

	enet_address_set_host(&netAddress, address.c_str());
	netAddress.port = port;

	// Connect to server.
	bool connected = false;
	for (int i = 0; i < 4; i++)
	{
		ServerPeer = enet_host_connect(ClientHost, &netAddress, 2, 0);
		if (!ServerPeer) { break; } // TODO: err, not 26

		if (enet_host_service(ClientHost, &event, 5000) > 0 && // TODO: timeout var?
			event.type == ENET_EVENT_TYPE_CONNECT)
		{
			connected = true;
			break;
		}
		enet_peer_reset(ServerPeer); // TODO: print failure 1, 2, 3, 4
	}
	if (!connected) return false;

	// Send client data.
	ENetPacket* packet;
	ClientData data = ClientData(Settings.PlayerName);
	ByteStream stream = data.ToStream();

	packet = enet_packet_create(stream.GetData(), stream.GetSize(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(ServerPeer, 0, packet);
	enet_host_flush(ClientHost);
	enet_packet_destroy(packet);
}

Client::Client()
{
	Settings = GameSettings::Load();

	if (!glfwInit()) // GLFW failed to initialize.
		throw 1; // TODO: error

	if (enet_initialize()) // enet failed to initialize.
		throw 2; // TODO: error

	// Set up window hints based on settings.
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_VISIBLE, false);
	if (Settings.WindowType == WindowType::BorderlessWindow)
		glfwWindowHint(GLFW_DECORATED, false);

	Window = glfwCreateWindow(Settings.WindowWidth, Settings.WindowHeight,
		"Watchtower", nullptr, nullptr);

	// Do not continue if the window failed to create.
	if (Window)
	{
		glfwMakeContextCurrent(Window);
		glewExperimental = true;
		if (glewInit() == GLEW_OK)
			Initialize();
		else {} // TODO: error
	}
	// Terminate GLFW after we've finished. Same for enet.
	glfwTerminate();
	enet_deinitialize();
}
