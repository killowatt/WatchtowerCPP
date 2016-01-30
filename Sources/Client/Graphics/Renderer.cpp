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
		Render(chunks[i].VertexArray);
	}
}

void Renderer::UpdateChunk(unsigned int offset)
{
	if (offset > map->GetTotalChunks())
	{
	} // TODO: throw error!!

	chunks[offset].Generate(map->GetData()[offset]);
}
void Renderer::UpdateWorld()
{
	for (int i = 0; i < map->GetTotalChunks(); i++)
	{
		chunks[i].Generate(map->GetData()[i]);
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