#include "Renderer.h"
using namespace Watchtower;

void Renderer::Render(const VertexArray& vertexArray)
{
	if (!shader)
		return; // TODO: print warning no shader!!

	glUseProgram(shader->GetProgram()); // TODO: see if we can set this one time in SetShader
	glBindVertexArray(vertexArray.GetVertexArrayObject());
	glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBufferSize(),
		GL_UNSIGNED_INT, nullptr);
}
void Renderer::RenderWorld()
{
	for (int i = 0; i < map->GetTotalChunks(); i++)
	{
		glUseProgram(shader->GetProgram());
		shader->Model = chunks[i].Transform;
		shader->Update();
		Render(chunks[i].VertexArray);
	}
}

void Renderer::UpdateChunk(unsigned int x, unsigned int y)
{
	if (x > map->GetWidth() || y > map->GetHeight())
	{
	} // TODO: throw error!!

	chunks[map->GetWidth() * y + x].Generate(map->GetChunk(x, y), x, y);
}
void Renderer::UpdateWorld()
{
	for (int x = 0; x < map->GetWidth(); x++)
	{
		for (int y = 0; y < map->GetHeight(); y++)
		{
			chunks[map->GetWidth() * y + x].Generate(map->GetChunk(x, y), x, y);
		}
	}
}

void Renderer::SetCamera(Camera camera) { this->camera = camera; }
Camera& Renderer::GetCamera() { return camera; }

void Renderer::SetShader(Shader& shader) { this->shader = &shader; }
Shader& Renderer::GetShader() { return *shader; }

Renderer::Renderer(GameMap* map)
{
	this->map = map;
	chunks = new RenderChunk[map->GetTotalChunks()];
}
Renderer::~Renderer()
{
	if (chunks)
		delete[] chunks;
}