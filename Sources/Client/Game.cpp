#include "Game.h"

// temp
#include "Graphics/VertexBuffer.h"
#include <vector>
#include "Assets/lodepng.h"
#include "enet/enet.h"

void Game::Update()
{
	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;

	float speed = 6.0f;
	float mouseSpeed = 0.05f;

	double xpos; // TODO: when we port this mouse code actually make it nice
	double ypos;
	glfwGetCursorPos(Window, &xpos, &ypos);
	glfwSetCursorPos(Window, 1280 / 2, 720 / 2);
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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


	camera.Update();
}
void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(xyzizzle->GetProgram());

	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			glBindVertexArray(world->GetChunk(x, y).VertexArray.GetVertexArrayObject());

			xyzizzle->Model = world->GetChunk(x, y).Transform;
			xyzizzle->Update();

			glDrawElements(GL_TRIANGLES, world->GetChunk(x, y).VertexArray.GetIndexBufferSize(),
				GL_UNSIGNED_INT, nullptr);
		}
	}
}
void Game::Initialize()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(20.0f / 255, 20.0f / 255, 20.0f / 255, 1.0f);

	camera = Graphics::Camera();
	camera.Position.z = -4;
	//camera.Rotation.y = 3.14159;
	

	// temp
	xyzizzle = new TestShader(camera);

	glUseProgram(xyzizzle->GetProgram());
	xyzizzle->Initialize();

	glUseProgram(0);


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

	world = new World(16, 16);
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
						world->GetChunk(cx, cy).Blocks[bx][bz][by].Active = true;
						world->GetChunk(cx, cy).Blocks[bx][bz][by].Color =
							glm::vec3((bz / 127.0f), 40.0f / 255.0f, 94.0f / 255.0f);
					}
				}
			}
		}
	}
	world->Update();


	std::cout << "Size of chunk is " << sizeof(Chunk) << "\n";

	// Network
	if (enet_initialize() != 0)
	{
		std::cout << "Network failed to initialize.\n";
		return;
	}
	std::cout << "Network initialized.\n";

	std::cout << "Initializing client.. \n";
	ENetHost* client;
	client = enet_host_create(nullptr, 1, 2, 57600 / 8, 14400 / 8);

	if (client == nullptr)
	{
		std::cout << "Failed to create client. \n";
		return;
	}

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

	// Receive chunks
	bool receivingChunks = true;
	while (receivingChunks)
	{
		while (enet_host_service(client, &event, 1000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "Connected to ";
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

	enet_deinitialize();
	// End Network

	std::cout << "INITIALIZED!!!!!!!!!! \n";
	std::cout << "GL Error State: " << glGetError() << std::endl;
	std::cout << xyzizzle->GetCompileLog(Graphics::ShaderType::Vertex) << std::endl;
	std::cout << xyzizzle->GetCompileLog(Graphics::ShaderType::Fragment) << std::endl;

	glfwSetCursorPos(Window, 1280 / 2, 720 / 2);
}

Game::Game(GLFWwindow* window)
{
	std::cout << "WE ARE STARTING \n";
	Window = window;
	Running = true;

	Initialize();
	while (!glfwWindowShouldClose(window) && Running)
	{
		Update();
		Render();
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}