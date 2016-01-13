#include "OldClient.h"

// temp
#include "Graphics/VertexBuffer.h"
#include <vector>
#include "Assets/lodepng.h"
#include "enet/enet.h"
#include "ByteStream.h"
#include "zlib/zlib.h"
#include <cmath>
#include <Raycast.h>

using namespace Watchtower;

void Clientx::Update()
{
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
			Raycast::RaycastBlock(camera.Direction * 8.0f, 8, false, camera.Position, world);
			renderer.mapRenderer.UpdateChunk(Raycast::chunkToUpdate.x, Raycast::chunkToUpdate.y);
		}
		else if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			Raycast::RaycastBlock(camera.Direction * 8.0f, 8, true, camera.Position, world);
			renderer.mapRenderer.UpdateChunk(Raycast::chunkToUpdate.x, Raycast::chunkToUpdate.y);
		}
	}
}
void Clientx::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.mapRenderer.Render(renderer);
}
void Clientx::Initialize()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(20.0f / 255, 20.0f / 255, 20.0f / 255, 1.0f);

	camera = Camera();
	camera.Position.z = -4;
	//camera.Rotation.y = 3.14159;
	

	// temp
	xyzizzle = new BasicColorShader(camera);

	glUseProgram(xyzizzle->GetProgram());
	xyzizzle->Initialize();

	glUseProgram(0);

	//// Here we load in a test heightmap just for kicks okay
	//std::vector<unsigned char> image;
	//unsigned int width, height;
	//lodepng::decode(image, width, height, "terrain_128_height.png");

	//unsigned char r[256 * 256];
	//int stride = 1024; // 256 pixels wide * 4 channels
	//int count = 0;

	//for (int row = 0; row < height; row++)
	//{
	//	for (int column = 0; column < width; column++)
	//	{
	//		r[count++] = image[(row * stride) + (column * 4)];
	//	}
	//}

	//world = new World(16, 16);
	//for (int cx = 0; cx < 16; cx++)
	//{
	//	for (int cy = 0; cy < 16; cy++)
	//	{
	//		for (int bx = 0; bx < 16; bx++)
	//		{
	//			for (int by = 0; by < 16; by++)
	//			{
	//				for (int bz = 0; bz <
	//					r[(width * (bx + (cx * 16))) + (by + (cy * 16))] / 1; bz++)
	//				{
	//					world->GetChunk(cx, cy).GetBlock(bx, bz, by).Active = true;
	//					world->GetChunk(cx, cy).GetBlock(bx, bz, by).Color =
	//						Color(bz * 2, 40, 94);
	//				}
	//			}
	//		}
	//	}
	//}


	std::cout << "Size of block is " << sizeof(Block) << "\n";

	// Network
	if (enet_initialize() != 0)
	{
		std::cout << "Network failed to initialize.\n";
		return;
	}
	std::cout << "Network initialized.\n";

	std::cout << "Initializing client.. \n";
	ENetHost* client;
	client = enet_host_create(nullptr, 1, 2, 0, 0);

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

	if (enet_host_service(client, &event, 10000) > 0 &&
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

	world = new GameMap(16, 16);
	// Receive chunks
	int countc = 0;
	bool receiving = true;
	while (receiving)
	{
		while (enet_host_service(client, &event, 10) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "Connected to ";
				std::cout << event.peer->address.host << ":"
					<< event.peer->address.port << "\n";
				break;
			case ENET_EVENT_TYPE_RECEIVE:
			{
				std::cout << "Received a packet.\n";
				std::cout << "Data Length: " << event.packet->dataLength << "\n";
				//std::cout << "Data: " << event.packet->data << "\n";
				std::cout << "Peer: " << event.peer->address.host << "\n";
				std::cout << "Channel: " << event.channelID << "\n";



				//int* x;
				//x = (int*)event.packet->data;

				//std::cout << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << " ";

				//Block* blokkszz = new Block[16 * 16];
				//chunkszz = (Chunk*)event.packet->data

				Chunk* chhh = new Chunk();

				z_stream infstream;
				infstream.zalloc = Z_NULL;
				infstream.zfree = Z_NULL;
				infstream.opaque = Z_NULL;
				infstream.avail_in = sizeof(Chunk);
				infstream.next_in = (Bytef*)event.packet->data;
				infstream.avail_out = sizeof(Chunk);
				infstream.next_out = (Bytef*)chhh;

				inflateInit(&infstream);
				inflate(&infstream, Z_NO_FLUSH);
				inflateEnd(&infstream);

				for (int x = 0; x < 16; x++)
				{
					for (int y = 0; y < 128; y++)
					{
						for (int z = 0; z < 16; z++)
						{

							world->GetData()[countc].GetBlock(x, y, z) = chhh->GetBlock(x, y, z);
						}
					}
				}

				countc++;
				std::cout << "PACKET# " << countc << "\n";
				std::cout << "SIzE " << infstream.total_in << "\n";
				if (countc > 255)
				{
					receiving = false;
				}
				//world->chunks[count].Blocks = (Block)event.packet->data;


				enet_packet_destroy(event.packet);
				//count++;
				//if (count >= 16 * 16)
				//{
				//	receiving = false;
				//}
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "Peer " << event.peer->data << " disconnected. \n";
				receiving = false;
				break;
			default:
				std::cout << "An unknown event was triggered.";
				break;
			}
		}
	}

	enet_deinitialize();

	renderer = Renderer(world);
	renderer.SetShader(*xyzizzle);
	renderer.Update();
	renderer.mapRenderer.UpdateMap();

	// End Network

	std::cout << "INITIALIzED!!!!!!!!!! \n";
	std::cout << "GL Error State: " << glGetError() << std::endl;
	std::cout << xyzizzle->GetCompileLog(ShaderType::Vertex) << std::endl;
	std::cout << xyzizzle->GetCompileLog(ShaderType::Fragment) << std::endl;

	glfwSetCursorPos(Window, 1280 / 2, 720 / 2);
	

}

Clientx::Clientx(GLFWwindow* window)
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