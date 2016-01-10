#include "Client.h"

// temp
#include "Graphics/VertexBuffer.h"
#include <vector>
#include "Assets/lodepng.h"
#include "enet/enet.h"
#include "ByteStream.h"
#include "zlib/zlib.h"
#include <cmath>

using namespace Common;

float mod(float value, float modulus) // So temporary
{
	//return value % modulus;
	//return fmod(value, modulus);
	return fmod((fmod(value, modulus) + modulus), modulus);
}
bool Clientx::callback(int xCopy, int yCopy, int zCopy,
	glm::ivec3 face, glm::vec3 direction, bool active)
{
	int cx = (int)floor(xCopy / 16);
	int cy = (int)floor(zCopy / 16);
	int bx = (int)mod(xCopy, 16);
	int by = (int)mod(yCopy, 128);
	int bz = (int)mod(zCopy, 16);

	// bx = xCopy % 16;
	// by = yCopy % 16;
	// bz = zCopy % 16;

	if ((bx > -1 && bx < 16) && (by > -1 && by < 128) && (bz > -1 && bz < 16))
	{
		if (world->GetChunk(cx, cy).GetBlock(bx, by, bz).Active)
		{
			if (active)
			{
				xCopy += face.x;
				yCopy += face.y;
				zCopy += face.z;
			}
			cx = (int)floor(xCopy / 16);
			cy = (int)floor(zCopy / 16);
			bx = (int)mod(xCopy, 16);
			by = (int)mod(yCopy, 128);
			bz = (int)mod(zCopy, 16);

			if (!active)
			{
				world->GetChunk(cx, cy).GetBlock(bx, by, bz).Active = false;
			}
			if (active)
			{
				//if ((bx + (int)face.x > -1 && bx + (int)face.x < 16) && (by + (int)face.y > -1 && by + (int)face.y < 128) && (bz + (int)face.z > -1 && bz + (int)face.z < 16))
				//{
				//	world->GetChunk(cx, cy).GetBlock(bx + (int)face.x, by + (int)face.y, bz + (int)face.z).Active = true;
				//	world->GetChunk(cx, cy).GetBlock(bx + (int)face.x, by + (int)face.y, bz + (int)face.z).Color = Color(1, 1, 1);
				//}

				
				if ((bx > -1 && bx < 16) && (by > -1 && by < 128) && (bz > -1 && bz < 16))
				{
					world->GetChunk(cx, cy).GetBlock(bx, by, bz).Active = true;
					world->GetChunk(cx, cy).GetBlock(bx, by, bz).Color = Color(255, 255, 255);
				}
			}

			chunkToUpdate = glm::ivec2(cx, cy);

			std::cout << "dir " << camera.Direction.x << " " <<
				camera.Direction.y << " " << camera.Direction.z << "\n";

			std::cout << "chunk " << cx << " " << cy << "\n";
			std::cout << "block " << bx << " " << by << " " << bz << "\n";
			std::cout << "copy " << xCopy << " " << yCopy << " " << zCopy << "\n";
			return true;
		}
	}
	return false;
}
static float intbound(float s, float ds)
{
	if (ds < 0)
		return intbound(-s, -ds);

	s = mod(s, 1);
	return (1 - s) / ds;

}
static int signum(float x)
{
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}
//public static void DrawACube(glm::vec3 pos)
//{
//    GL.Begin(BeginMode.Quads);

//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, 0.0f) + pos);

//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, -0.5f) + pos);

//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, 0.0f) + pos);

//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, 0.0f) + pos);

//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.5f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.5f, -0.5f) + pos);

//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, 0.0f) + pos);
//    GL.Vertex3(new glm::vec3(0.5f, 0.0f, -0.5f) + pos);
//    GL.Vertex3(new glm::vec3(0.0f, 0.0f, -0.5f) + pos);

//    GL.End();
//}
void Clientx::raycast(glm::vec3 direction, float radius, bool active)
{
	glm::vec3 origin(0, 0, 0);

	int x = (int)floor(camera.Position.x);
	int y = (int)floor(camera.Position.y);
	int z = (int)floor(camera.Position.z);

	int wx = 256;
	int wy = 256;
	int wz = 256; // WORLD BOUNDS

	float dx = direction.x;
	float dy = direction.y;
	float dz = direction.z;

	int stepx = signum(dx);
	int stepy = signum(dy);
	int stepz = signum(dz);

	float tMaxx = intbound(camera.Position.x, dx);
	float tMaxy = intbound(camera.Position.y, dy);
	float tMaxz = intbound(camera.Position.z, dz);

	float tDeltax = stepx / dx;
	float tDeltay = stepy / dy;
	float tDeltaz = stepz / dz;

	glm::ivec3 face(0, 0, 0);

	// Avoids an infinite loop.
	if (dx == 0 && dy == 0 && dz == 0)
		return;

	// Rescale from units of 1 cube-edge to units of 'direction' so we can
	// compare with 't'.
	radius /= sqrtf(dx * dx + dy * dy + dz * dz);

	while (/* ray has not gone past bounds of world */
		(stepx > 0 ? x < wx : x >= 0) &&
		(stepy > 0 ? y < wy : y >= 0) &&
		(stepz > 0 ? z < wz : z >= 0))
	{

		// Invoke the callback, unless we are not *yet* within the bounds of the
		// world.
		if (!(x < 0 || y < 0 || z < 0 || x >= wx || y >= wy || z >= wz))
		{
			if (callback(x, y, z, face, direction, active))
				break;
		}

		if (tMaxx < tMaxy)
		{
			if (tMaxx < tMaxz)
			{
				if (tMaxx > radius)
					break;
				// Update which cube we are now in.
				x += stepx;
				// Adjust tMaxx to the next x-oriented boundary crossing.
				tMaxx += tDeltax;
				// Record the normal vector of the cube face we entered.
				face.x = -stepx;
				face.y = 0;
				face.z = 0;
			}
			else
			{
				if (tMaxz > radius)
					break;
				z += stepz;
				tMaxz += tDeltaz;
				face.x = 0;
				face.y = 0;
				face.z = -stepz;
			}
		}
		else
		{
			if (tMaxy < tMaxz)
			{
				if (tMaxy > radius)
					break;
				y += stepy;
				tMaxy += tDeltay;
				face.x = 0;
				face.y = -stepy;
				face.z = 0;
			}
			else
			{
				// Identical to the second case, repeated for simplicity in
				// the conditionals.
				if (tMaxz > radius)
					break;
				z += stepz;
				tMaxz += tDeltaz;
				face.x = 0;
				face.y = 0;
				face.z = -stepz;
			}
		}
	}
}



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
				raycast(camera.Direction * 8.0f, 8, false);
				renderer.UpdateChunk(chunkToUpdate.x, chunkToUpdate.y);
		}
		else if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
				raycast(camera.Direction * 8.0f, 8, true);
				renderer.UpdateChunk(chunkToUpdate.x, chunkToUpdate.y);
		}
	}
}
void Clientx::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.RenderMap();
}
void Clientx::Initialize()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(20.0f / 255, 20.0f / 255, 20.0f / 255, 1.0f);

	camera = Client::Camera();
	camera.Position.z = -4;
	//camera.Rotation.y = 3.14159;
	

	// temp
	xyzizzle = new TestShader(camera);

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
	//						Client::Color(bz * 2, 40, 94);
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

	world = new Common::GameMap(16, 16);
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

				Common::Chunk* chhh = new Common::Chunk();

				z_stream infstream;
				infstream.zalloc = Z_NULL;
				infstream.zfree = Z_NULL;
				infstream.opaque = Z_NULL;
				infstream.avail_in = sizeof(Common::Chunk);
				infstream.next_in = (Bytef*)event.packet->data;
				infstream.avail_out = sizeof(Common::Chunk);
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


	renderer.SetShader(*xyzizzle);
	renderer.SetMap(*world);
	renderer.Update();

	// End Network

	std::cout << "INITIALIzED!!!!!!!!!! \n";
	std::cout << "GL Error State: " << glGetError() << std::endl;
	std::cout << xyzizzle->GetCompileLog(Client::ShaderType::Vertex) << std::endl;
	std::cout << xyzizzle->GetCompileLog(Client::ShaderType::Fragment) << std::endl;

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