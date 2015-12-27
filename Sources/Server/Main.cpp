#include <iostream>
#include <string>
#include <enet/enet.h>

void Client()
{
	std::cout << "Initializing client. \n";

	// Client Setup
	ENetHost* client;

	client = enet_host_create(nullptr, 1, 2, 57600 / 8, 14400 / 8);

	if (client == nullptr)
		return;

	// Connection
	ENetAddress address;
	ENetEvent event;
	ENetPeer *peer;

	std::cout << "Please enter the host address. \n";
	std::string inputAddress;
	std::getline(std::cin, inputAddress);

	enet_address_set_host(&address, inputAddress.c_str());
	address.port = 22737;

	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == nullptr)
		return;

	std::cout << "Press enter when you want to connect.\n";
	getchar();

	if (enet_host_service(client, &event, 5000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Successfully connected to host. \n";
	}
	else
	{
		std::cout << "Failed to connect to host. \n";
		enet_peer_reset(peer);
		return;
	}
	enet_host_flush(client);

	while (true)
	{
		std::cout << "Press enter a string to send as a packet.\n";
		std::string packetContent;
		std::getline(std::cin, packetContent);

		ENetPacket* packet = enet_packet_create(packetContent.c_str(),
			strlen(packetContent.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);

		enet_peer_send(peer, 0, packet);
		enet_host_flush(client);
	}

	// Destroy
	enet_host_destroy(client);
}
void ServerChunk()
{
	std::cout << "Initializing server. \n";
	ENetAddress address;
	ENetHost* server;

	address.host = ENET_HOST_ANY;
	address.port = 22737;

	server = enet_host_create(&address, 32, 2, 0, 0);

	if (server == nullptr)
		return;

	std::cout << "Successfully created server. Now waiting for client. \n";
	ENetEvent event;
	bool waitingForClient = true;
	while (waitingForClient)
	{
		while (enet_host_service(server, &event, 1000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "Client connected.\n";
				std::cout << event.peer->address.host << ":"
					<< event.peer->address.port << "\n";

				waitingForClient = false;
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Received a packet.\n";
				std::cout << "Data Length: " << event.packet->dataLength << "\n";
				std::cout << "Data: " << event.packet->data << "\n";
				std::cout << "Peer: " << event.peer->data << "\n";
				std::cout << "Channel: " << event.channelID << "\n";

				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "Peer " << event.peer->data << " disconnected. \n";
				break;
			default:
				std::cout << "An unknown event was triggered.";
				break;
			}
		}
	}

	std::cout << "Now preparing to send chunks. \n";
	ENetPacket* packet = enet_packet_create("YO MANE",
		strlen("YO MANE") + 1, ENET_PACKET_FLAG_RELIABLE);

	enet_host_broadcast(server, 0, packet);
	enet_host_flush(server);

	enet_host_destroy(server);
}
void Server()
{
	std::cout << "Initializing server. \n";
	ENetAddress address;
	ENetHost* server;

	address.host = ENET_HOST_ANY;
	address.port = 22737;

	server = enet_host_create(&address, 32, 2, 0, 0);

	if (server == nullptr)
		return;

	std::cout << "Successfully created server. Now waiting for packet. \n";
	ENetEvent event;
	while (true)
	{
		while (enet_host_service(server, &event, 1000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "Client connected.\n";
				std::cout << event.peer->address.host << ":"
					<< event.peer->address.port << "\n";
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Received a packet.\n";
				std::cout << "Data Length: " << event.packet->dataLength << "\n";
				std::cout << "Data: " << event.packet->data << "\n";
				std::cout << "Peer: " << event.peer->data << "\n";
				std::cout << "Channel: " << event.channelID << "\n";

				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "Peer " << event.peer->data << " disconnected. \n";
				break;
			default:
				std::cout << "An unknown event was triggered.";
				break;
			}
		}
	}

	enet_host_destroy(server);
}
int main()
{
	if (enet_initialize() != 0)
		return 0;

	std::cout << "Type CLIENT if you are a CLIENT. \n";
	std::cout << "Type SERVER if you are a SERVER. \n";
	std::cout << "Type TEST if you are a CHUNK SERVER. \n";

	std::string input;
	std::getline(std::cin, input);
	if (input == "CLIENT")
		Client();
	else if (input == "SERVER")
		Server();
	else if (input == "TEST")
		ServerChunk();
	else
		std::cout << "Man you typed the wrong thing.. \n";
	
	std::cout << "Execution complete. Press enter to quit. \n";
	getchar();

	enet_deinitialize();
}