#include "Game.h"

// temp
#include "Graphics/VertexBuffer.h"
#include <vector>

void Game::Update()
{
}
void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(cubevao->GetVertexArrayObject());
	glUseProgram(xyzizzle->GetProgram());

	xxxTEST += 0.05f;
	camera.Position = glm::vec3(3 * sin(xxxTEST), 1, 3 * cos(xxxTEST));
	camera.Rotation.x = 3.14159f + xxxTEST;
	camera.Rotation.y = -3.14159f / 9;
	camera.Update();

	xyzizzle->Update();

	glDrawElements(GL_TRIANGLES, cubevao->GetIndexBufferSize(), GL_UNSIGNED_INT, nullptr);
}
void Game::Initialize()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(20.0f / 255, 20.0f / 255, 20.0f / 255, 1.0f);

	camera = Graphics::Camera();

	// temp
	xyzizzle = new TestShader(camera);

	glUseProgram(xyzizzle->GetProgram());
	xyzizzle->Initialize();

	glUseProgram(0);
	cubevbo = new Graphics::VertexBuffer();
	cubevao = new Graphics::VertexArray();

	cubevbo->SetBufferData({ -1, 1, 1, 1, -1, -1, 1, -1 }, 2, Graphics::MemoryHint::Static);
	cubevao->AttachBuffer(*cubevbo, 0);
	cubevao->SetIndexBuffer({ 0, 1, 2, 2, 1, 3 });


	std::cout << "INITIALIZED!!!!!!!!!! \n";
	std::cout << "GL Error State: " << glGetError() << std::endl;
	std::cout << xyzizzle->GetCompileLog(Graphics::ShaderType::Vertex) << std::endl;
	std::cout << xyzizzle->GetCompileLog(Graphics::ShaderType::Fragment) << std::endl;
}

Game::Game(GLFWwindow* window)
{
	std::cout << "WE ARE STARTING \n";
	Window = window;

	Initialize();
	while (!glfwWindowShouldClose(window))
	{
		Update();
		Render();
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}