#include "Chunk.h"

using namespace Graphics;

void Chunk::Update()
{

}

Chunk::Chunk()
{
	Blocks = new Block**[CHUNK_WIDTH];
	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		Blocks[x] = new Block*[CHUNK_HEIGHT];
		for (int y = 0; y < CHUNK_LENGTH; y++)
		{
			Blocks[x][y] = new Block[CHUNK_LENGTH];
		}
	}
}
Chunk::~Chunk()
{
	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_LENGTH; y++)
		{
			delete[] Blocks[x][y];
		}
		delete[] Blocks[x];
	}
	delete[] Blocks;
}