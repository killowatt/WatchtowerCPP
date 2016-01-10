#pragma once
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GameMap.h>
#include "VertexArray.h"
#include "Shader.h"
#include "ChunkRenderData.h"

namespace Client
{
	class Renderer
	{
	private:
		Common::GameMap* currentMap;
		ChunkRenderData* mapRenderData;
		Shader* currentShader;

	public:
		void Render(const VertexArray& vertexArray);
		void Render(const VertexBuffer& vertexBuffer);
		void RenderMap();

		void Update();
		void UpdateChunk(unsigned int x, unsigned int y);

		void SetShader(Shader& shader);
		Shader& GetShader();

		void SetMap(Common::GameMap& map);
		Common::GameMap& GetMap();
		void RemoveMap();

		Renderer();
		~Renderer();
	};
}