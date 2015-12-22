#pragma once

#include "Block.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"

class Chunk
{
public:
	Block*** Blocks; // TODO: one dimensional array for performance, using a method to access and change blocks given xyz.
	static const int CHUNK_WIDTH = 16;
	static const int CHUNK_DEPTH = 16;
	static const int CHUNK_HEIGHT = 128;

	Graphics::VertexArray vertexArray;
	Graphics::VertexBuffer vertices;
	Graphics::VertexBuffer colors;
	Graphics::VertexBuffer normals;

public:
	void Update();
	void ExperimentalUpdate();

	Chunk();
	~Chunk();
};