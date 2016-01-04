#pragma once

#include <Chunk.h>

struct Chunk : Common::Chunk
{
public:
	static const int CHUNK_WIDTH = 16;
	static const int CHUNK_HEIGHT = 128;
	static const int CHUNK_DEPTH = 16;
	Block Blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];

	Chunk();
	~Chunk();
};