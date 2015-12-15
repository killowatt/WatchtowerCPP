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

class TestShader : public Graphics::Shader
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
		//Model = Model * glm::translate(glm::mat4(1.0), glm::vec3(0.01f, 0, 0));
		glUniformMatrix4fv(modelLocation, 1, false, &Model[0][0]);
	}

	TestShader()
		: Graphics::Shader(ReadFile("Test.v"), ReadFile("Test.f"),
			Graphics::ShaderState::Static)
	{
		glm::mat4 m1 = glm::translate(glm::mat4(1.0), glm::vec3(640.0f, 360.0f, 0.0f));
		Model = glm::scale(m1, glm::vec3(150 / 2, 150 / 2, 150.0f));
		Projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f);
		std::cout << "Help, I WAS INITIALIZED \n";
	}
};

class Game
{
public:
	GLFWwindow* Window;

	// Temp tests
	TestShader* xyzizzle;
	Graphics::VertexBuffer* cubevbo;
	Graphics::VertexArray* cubevao;

	void Initialize();
	void Update();
	void Render();

	bool Running;

	Game(GLFWwindow* window);
};