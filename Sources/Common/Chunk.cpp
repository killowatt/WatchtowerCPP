#include "Chunk.h"

using namespace Watchtower;

Block& Chunk::GetBlock(int x, int y, int z)
{
	return blocks[x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z)];
}
void Chunk::SetBlock(int x, int y, int z, Block block)
{
	blocks[x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z)] = block;
}

Chunk::Chunk() {}