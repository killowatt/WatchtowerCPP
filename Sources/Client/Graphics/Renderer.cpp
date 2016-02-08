#include "Renderer.h"
using namespace Watchtower;

void Renderer::Render(const VertexArray& vertexArray)
{
	Render(vertexArray, glm::mat4());
}
void Renderer::Render(const VertexArray& vertexArray, const glm::mat4& transform)
{
	if (!shader)
		return; // TODO: print warning no shader!!

	glUseProgram(shader->GetProgram());
	shader->Model = transform;
	shader->Update();

	glBindVertexArray(vertexArray.GetVertexArrayObject());
	glDrawElements(GL_TRIANGLES, vertexArray.GetIndexBufferSize(),
		GL_UNSIGNED_INT, nullptr);
}
void Renderer::RenderWorld()
{
	if (!shader)
		return; // TODO: THIS JEEZ

	for (int i = 0; i < map->GetTotalChunks(); i++)
	{
		glUseProgram(shader->GetProgram());
		shader->Model = chunks[i].Transform;
		shader->Update();

		glBindVertexArray(chunks[i].VertexArray.GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, chunks[i].VertexArray.GetIndexBufferSize(),
			GL_UNSIGNED_INT, nullptr);
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