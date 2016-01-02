#pragma once
#include <Chunk.h>

class World
{
public:
	Common::Chunk* chunks;

	unsigned int width;
	unsigned int height;

public:
	Common::Chunk& GetChunk(unsigned int x, unsigned int y); // TODO: consider the overall system for blocks and chunks and how it can be improved..
	unsigned int GetWidth();
	unsigned int GetHeight();

	World() = delete;
	World(unsigned int width, unsigned int height);
	~World();
};