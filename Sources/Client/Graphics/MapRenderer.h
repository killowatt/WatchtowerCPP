#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <Chunk.h>
#include "VertexArray.h"

namespace Client
{
	struct MapRenderer
	{
	private:
		struct RenderChunk
		{
			VertexArray VertexArray;
			VertexBuffer Vertices;
			VertexBuffer Colors;
			VertexBuffer Normals;

			void Generate(const Common::Chunk& chunk);
		};

	public:
		RenderChunk* vertexData;
		glm::mat4x4* chunkTransforms;

		void SetMap();

		MapRenderer();
		~MapRenderer();
	};
}