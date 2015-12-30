#pragma once

#include "Block.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "glm/glm.hpp"

struct Chunk
{
public:
	static const int CHUNK_WIDTH = 16;
	static const int CHUNK_HEIGHT = 128;
	static const int CHUNK_DEPTH = 16;
	Block Blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
	glm::mat4 Transform;

	Graphics::VertexArray VertexArray;
	Graphics::VertexBuffer Vertices;
	Graphics::VertexBuffer Colors;
	Graphics::VertexBuffer Normals;

	void Update();

	Chunk();
	~Chunk();
};