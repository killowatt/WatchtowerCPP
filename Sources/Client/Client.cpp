#include "Client.h"
#include <iostream>
#include <ByteStream.h>
#include <Network/Packets.h>


#include <Raycast.h>


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

	glfwShowWindow(Window);

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
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}
void Client::Update()
{
	ENetEvent event;
	while (enet_host_service(ClientHost, &event, 0) > 0)
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
				std::cout << "Map Width: " << mapInfo.Width << "\n";
				std::cout << "Map Width: " << mapInfo.Height << "\n";
				CurrentMap = new GameMap(mapInfo.Width, mapInfo.Height);
				Renderer = new Watchtower::Renderer(CurrentMap);
			}
			if (packetType == PacketType::MapData)
			{
				std::cout << "Chunk Packet #" << xyz << " received." << "\n";
				MapData::Read(event.packet, &CurrentMap->GetData()[xyz]); // TODO: TRASH
				if (xyz >= 255)
				{
					Renderer->UpdateWorld();
					DESTRUCTION = true;
					Renderer->Camera.Rotation.y = 3.14159f / 2;
					shaderB = new BasicColorShader(Renderer->Camera);
					glUseProgram(shaderB->GetProgram());
					shaderB->Initialize();
					Renderer->SetShader(*shaderB);
				}
				xyz++;
			}
			enet_packet_destroy(event.packet);
		}
		else if (event.type == ENET_EVENT_TYPE_DISCONNECT)
		{
			printf("Disconnected.");
		}
	}

	Camera& camera = Renderer->Camera;

	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;

	float speed = 6.0f;
	float mouseSpeed = 0.05f;

	double xpos; // TODO: when we port this mouse code actually make it nice
	double ypos;

	if (glfwGetWindowAttrib(Window, GLFW_FOCUSED))
	{
		glfwGetCursorPos(Window, &xpos, &ypos);
		glfwSetCursorPos(Window, 1280 / 2, 720 / 2);
		//glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		camera.Rotation.x += mouseSpeed * deltaTime * float(1280 / 2 - xpos);
		camera.Rotation.y += mouseSpeed * deltaTime * float(720 / 2 - ypos);

		if (glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			speed = 12.0f;
		else
			speed = 6.0f;

		// Move forward
		if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
			camera.Position += camera.Direction * deltaTime * speed;

		// Move backward
		if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
			camera.Position -= camera.Direction * deltaTime * speed;

		// Strafe right
		if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
			camera.Position += camera.Right * deltaTime * speed;

		// Strafe left
		if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
			camera.Position -= camera.Right * deltaTime * speed;

		// Go up
		if (glfwGetKey(Window, GLFW_KEY_SPACE) == GLFW_PRESS)
			camera.Position.y += deltaTime * speed;

		// Go down
		if (glfwGetKey(Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			camera.Position.y -= deltaTime * speed;

		if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			Running = false;

		if (glfwGetKey(Window, GLFW_KEY_H) == GLFW_PRESS)
		{
			camera.Rotation.x = 0;
			camera.Rotation.y = 0;
		}

		camera.Update();


		if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			Raycast::RaycastBlock(camera.Direction * 8.0f, 8, false, camera.Position, CurrentMap);
			Renderer->UpdateChunk(Raycast::chunkToUpdate.x, Raycast::chunkToUpdate.y);
		}
		else if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			Raycast::RaycastBlock(camera.Direction * 8.0f, 8, true, camera.Position, CurrentMap);
			Renderer->UpdateChunk(Raycast::chunkToUpdate.x, Raycast::chunkToUpdate.y);
		}

		Renderer->Camera.Update();
	}
}
void Client::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (DESTRUCTION)
	{
		Renderer->RenderWorld();
	}
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
}

Client::Client()
{
	Settings = GameSettings::Load();

	CurrentMap = nullptr;

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
