#pragma once

#include "Block.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"


class Chunk
{
public:
	Block*** Blocks;

	static const int CHUNK_WIDTH = 16;
	static const int CHUNK_LENGTH = 16;
	static const int CHUNK_HEIGHT = 128;

	Graphics::VertexArray vertexArray;
	Graphics::VertexBuffer vertices;
	Graphics::VertexBuffer colors;
	Graphics::VertexBuffer normals;

	void Update();

	Chunk();
	~Chunk();
};