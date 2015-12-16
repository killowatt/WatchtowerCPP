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

	xxxTEST += 0.05;
	//camera.SetPositionX(5 * sin(xxxTEST));
	//camera.SetPositionZ(5 * cos(xxxTEST));
	//camera.SetPositionY(0);
	//camera.SetPosition(glm::vec3(0, 0, -1));
	//camera.SetRotationY(xxxTEST);
	//camera.GetView() = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//camera.SetPositionZ(15);
	camera.SetPosition(glm::vec3(3 * sin(xxxTEST), 1, 3 * cos(xxxTEST)));
	camera.SetRotationY(3.14159 + xxxTEST);
	camera.SetRotationZ(-0.261799);
	//camera.SetRotationY(xxxTEST);
	//camera.SetRotation(glm::vec3(0, xxxTEST, 0));
	camera.Calculate();
	//xyzizzle->View = glm::mat4();
	xyzizzle->Update();

	glDrawElements(GL_TRIANGLES, cubevao->GetIndexBufferSize(), GL_UNSIGNED_INT, nullptr);
}
void Game::Initialize()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(20.0f / 255, 20.0f / 255, 20.0f / 255, 1.0f);

	camera = Graphics::Camera();
	//camera.SetPositionZ(-1);
	camera.SetZNear(0.001);
	//camera.SetMode(Graphics::CameraMode::Perspective);
	//camera.SetOrthoDimensions(0, 1280, 0, 720);

	// temp
	xyzizzle = new TestShader(camera);
	//projTEST = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f);
	//viewTEST = glm::mat4();
	//xyzizzle->View = viewTEST;
	//xyzizzle->Projection = projTEST;
	//

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