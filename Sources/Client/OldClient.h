//#pragma once
//#include <GLFW/glfw3.h>
//#include <GL/glew.h>
//
//// temp includes
//#include <iostream>
//#include "Graphics/Shader.h"
//#include "Graphics/VertexArray.h"
//#include "Graphics/VertexBuffer.h"
//#include "Assets/TempShaderLoader.h"
//#include <glm/mat4x4.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "Graphics/Camera.h"
//#include "Block.h"
//#include "Chunk.h"
//#include <GameMap.h>
//#include "Graphics/Renderer.h"
//#include "Assets/Shaders/BasicColorShader.h"
//
//using namespace Watchtower;
//
//class Clientx
//{
//public:
//	GLFWwindow* Window;
//	bool Running;
//
//	// Temp tests
//	BasicColorShader* xyzizzle;
//	//Chunk* chunk;
//	Camera camera;
//
//	float xTest;
//	double lastTime;
//	double currentTime;
//	float deltaTime;
//
//	//Chunk* chunks[16];
//	//glm::mat4 chunkTranslationTemp[16][16];
//
//	glm::ivec2 chunkToUpdate;
//	void raycast(glm::vec3 direction, float radius, bool active);
//	bool callback(int xCopy, int yCopy, int zCopy, glm::ivec3 face, glm::vec3 direction, bool active);
//	GameMap* world;
//	Renderer renderer;
//
//	//World* world;
//
//	void Initialize();
//	void Update();
//	void Render();
//
//	Clientx(GLFWwindow* window);
//};