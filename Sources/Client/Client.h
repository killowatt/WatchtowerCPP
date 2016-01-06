#pragma once
#include <GLFW/glfw3.h>
#include <GL/glew.h>

// temp includes
#include <iostream>
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Assets/TempShaderLoader.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Graphics/Camera.h"
#include "Block.h"
#include "Chunk.h"
#include "World.h"
#include "ChunkTempData.h"

class TestShader : public Client::Shader
{
public:
	int modelLocation;
	int viewLocation;
	int projectionLocation;

	void Initialize()
	{
		modelLocation = glGetUniformLocation(shaderProgram, "Model");
		viewLocation = glGetUniformLocation(shaderProgram, "View");
		projectionLocation = glGetUniformLocation(shaderProgram, "Projection");

		glUniformMatrix4fv(modelLocation, 1, false, &Model[0][0]);
		glUniformMatrix4fv(viewLocation, 1, false, &View[0][0]);
		glUniformMatrix4fv(projectionLocation, 1, false, &Projection[0][0]);
	}
	void Update()
	{
		glUniformMatrix4fv(modelLocation, 1, false, &Model[0][0]);
		glUniformMatrix4fv(viewLocation, 1, false, &View[0][0]);
		glUniformMatrix4fv(projectionLocation, 1, false, &Projection[0][0]);
	}

	TestShader(Client::Camera& camera)
		: Client::Shader(ReadFile("Test.v"), ReadFile("Test.f"),
			Client::ShaderState::Static, camera)
	{
		//glm::mat4 m1 = glm::translate(glm::mat4(1.0), glm::vec3(640.0f, 360.0f, 0.0f));
		//Model = glm::scale(m1, glm::vec3(150 / 2, 150 / 2, 150.0f));
	}
};

class Clientx
{
public:
	GLFWwindow* Window;
	bool Running;

	// Temp tests
	TestShader* xyzizzle;
	//Chunk* chunk;
	Client::Camera camera;

	float xTest;
	double lastTime;
	double currentTime;
	float deltaTime;

	//Chunk* chunks[16];
	glm::mat4 chunkTranslationTemp[16][16];

	Common::World* world;
	Client::ChunkTempData tempdata[16][16];

	void Initialize();
	void Update();
	void Render();

	Clientx(GLFWwindow* window);
};