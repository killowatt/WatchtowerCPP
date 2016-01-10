#include "MapRenderer.h"
#include "Renderer.h"
using namespace Client;

void MapRenderer::UpdateMap()
{
	if (vertexData)
		delete[] vertexData;
	if (chunkTransforms)
		delete[] chunkTransforms;
	if (!map)
		return;

	int size = map->GetWidth() * map->GetHeight();
	vertexData = new RenderChunk[size];
	chunkTransforms = new glm::mat4x4[size];

	for (int x = 0; x < map->GetWidth(); x++)
	{
		for (int y = 0; y < map->GetHeight(); y++)
		{
			vertexData[map->GetWidth() * y + x].Generate(map->GetChunk(x, y));
			chunkTransforms[map->GetWidth() * y + x] = glm::translate(glm::mat4(),
				glm::vec3(x * Common::Chunk::CHUNK_WIDTH, 0, y * Common::Chunk::CHUNK_DEPTH));
		}
	}
}
void MapRenderer::UpdateChunk(int x, int y)
{
	vertexData[map->GetWidth() * y + x].Generate(map->GetChunk(x, y));
}
void MapRenderer::Render(Renderer& renderer)
{
	if (!vertexData || !chunkTransforms)
		return;

	for (int i = 0; i < map->GetWidth() * map->GetHeight(); i++)
	{
		glUseProgram(renderer.GetShader().GetProgram());
		renderer.GetShader().Model = chunkTransforms[i];
		renderer.GetShader().Update();
		renderer.Render(vertexData[i].VertexArray);
	}
}

MapRenderer::MapRenderer()
{
	vertexData = nullptr;
	chunkTransforms = nullptr;
}
MapRenderer::MapRenderer(Common::GameMap* staticMap) : MapRenderer()
{
	map = staticMap;
}
MapRenderer::~MapRenderer()
{
	if (vertexData)
		delete[] vertexData;
	if (chunkTransforms)
		delete[] chunkTransforms;
}