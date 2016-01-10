#include "BasicColorShader.h"
using namespace Client;

void BasicColorShader::Initialize()
{
	modelLocation = glGetUniformLocation(shaderProgram, "Model");
	viewLocation = glGetUniformLocation(shaderProgram, "View");
	projectionLocation = glGetUniformLocation(shaderProgram, "Projection");

	glUniformMatrix4fv(modelLocation, 1, false, &Model[0][0]);
	glUniformMatrix4fv(viewLocation, 1, false, &View[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, false, &Projection[0][0]);
}
void BasicColorShader::Update()
{
	glUniformMatrix4fv(modelLocation, 1, false, &Model[0][0]);
	glUniformMatrix4fv(viewLocation, 1, false, &View[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, false, &Projection[0][0]);
}
BasicColorShader::BasicColorShader(Client::Camera& camera) 
	: Client::Shader(ReadFile("Test.v"), ReadFile("Test.f"),
		Client::ShaderState::Static, camera)
{
}