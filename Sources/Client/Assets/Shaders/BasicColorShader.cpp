#include "BasicColorShader.h"
using namespace Watchtower;

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
BasicColorShader::BasicColorShader(Camera& camera) 
	: Shader(ReadFile("Test.v"), ReadFile("Test.f"),
		ShaderState::Static, camera)
{
}