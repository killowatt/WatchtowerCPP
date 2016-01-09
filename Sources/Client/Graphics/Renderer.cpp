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
void Renderer::RenderMap()
{
	if (!mapRenderData)
		throw std::exception("map render data was null"); // TODO: replace. we should have an empty map
	                                                                                   // to replace
	for (int i = 0; i < currentMap->GetWidth() * currentMap->GetHeight(); i++)
	{
		glUseProgram(currentShader->GetProgram());
		currentShader->Model = mapRenderData[i].Transform;
		currentShader->Update();
		Render(mapRenderData[i].VertexArray);
	}
}

void Renderer::Update()
{
	if (!mapRenderData && currentMap)
		mapRenderData = new ChunkRenderData[currentMap->GetWidth() * currentMap->GetHeight()];
	for (int x = 0; x < currentMap->GetWidth(); x++)
	{
		for (int y = 0; y < currentMap->GetHeight(); y++)
		{
			mapRenderData[currentMap->GetWidth() * y + x].Generate(
				currentMap->GetChunk(x, y), x, y);
		}
	}
}

void Renderer::SetShader(Shader& shader)
{
	currentShader = &shader;
}
Shader& Renderer::GetShader()
{
	return *currentShader;
}

void Renderer::SetMap(Common::GameMap& map)
{
	currentMap = &map;
	delete[] mapRenderData;
}
Common::GameMap& Renderer::GetMap()
{
	return *currentMap;
}
void Renderer::RemoveMap()
{
}

Renderer::Renderer()
{
}
Renderer::~Renderer()
{
	delete mapRenderData;
}