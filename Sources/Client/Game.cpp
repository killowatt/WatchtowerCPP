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

	//xxxTEST += 0.05f;
	//camera.Position = glm::vec3(3 * sin(xxxTEST), 1, 3 * cos(xxxTEST));
	//camera.Rotation.x = 3.14159f + xxxTEST;
	//camera.Rotation.y = -3.14159f / 9;
	//camera.Update();

	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;

	float speed = 3.0f;
	float mouseSpeed = 0.05f;

	double xpos;
	double ypos;
	glfwGetCursorPos(Window, &xpos, &ypos);
	glfwSetCursorPos(Window, 1280 / 2, 720 / 2);
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	camera.Rotation.x += mouseSpeed * deltaTime * float(1280 / 2 - xpos);
	camera.Rotation.y += mouseSpeed * deltaTime * float(720 / 2 - ypos);

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

	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		Running = false;


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
	camera.Position.z = -4;
	//camera.Rotation.y = 3.14159;
	

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