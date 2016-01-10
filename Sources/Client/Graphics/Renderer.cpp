#include "Renderer.h"
using namespace Client;

void Renderer::Render(const VertexArray& vertexArray)
{
	glBindVertexArray(vertexArray.GetVertexArrayObject());
	glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBufferSize(),
		GL_UNSIGNED_INT, nullptr);
}
void Renderer::Render(const VertexBuffer& vertexBuffer)
{
	throw std::exception("not implemented, too lazy"); // TODO: this
}

void Renderer::Update()
{
}

void Renderer::SetShader(Shader& shader)
{
	currentShader = &shader;
}
Shader& Renderer::GetShader()
{
	return *currentShader;
}

Renderer::Renderer() {}
Renderer::Renderer(Common::GameMap* mapPtrTemp)
{
	mapRenderer = MapRenderer(mapPtrTemp);
}
Renderer::~Renderer()
{
}