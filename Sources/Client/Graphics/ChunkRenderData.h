#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <Chunk.h>
#include "VertexArray.h"

namespace Client
{
	struct ChunkRenderData
	{
	public:
		glm::mat4x4 Transform;
		VertexArray VertexArray;
		VertexBuffer Vertices;
		VertexBuffer Colors;
		VertexBuffer Normals;

		void Generate(Common::Chunk& chunk, int x, int y);

		ChunkRenderData();
	};
}