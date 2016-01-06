#pragma once

#include <glm/glm.hpp>
#include <Chunk.h>
#include "Block.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"

namespace Client
{
	class ChunkTempData
	{
	public:
		static const int CHUNK_WIDTH = 16;
		static const int CHUNK_HEIGHT = 128;
		static const int CHUNK_DEPTH = 16;

		glm::mat4 Transform;

		Client::VertexArray VertexArray;
		Client::VertexBuffer Vertices;
		Client::VertexBuffer Colors;
		Client::VertexBuffer Normals;


		void Update(Common::Chunk& chnk);

		ChunkTempData();
		~ChunkTempData();
	};
}