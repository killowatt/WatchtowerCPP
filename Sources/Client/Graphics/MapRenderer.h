#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <GameMap.h>
#include "VertexArray.h"

namespace Client
{
	class Renderer;
	class MapRenderer
	{
	private:
		struct RenderChunk
		{
			VertexArray VertexArray;
			VertexBuffer Vertices;
			VertexBuffer Colors;
			VertexBuffer Normals;

			void Generate(Common::Chunk& chunk);
		};

		Common::GameMap* map;
		RenderChunk* vertexData;
		glm::mat4x4* chunkTransforms; 

	public:
		void UpdateMap();
		void UpdateChunk(int x, int y);
		void Render(Renderer& renderer);

		MapRenderer();
		MapRenderer(Common::GameMap* staticMap); // TODO: point to world map eventually
		~MapRenderer();
	};
}