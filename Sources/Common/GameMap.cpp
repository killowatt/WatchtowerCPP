#include "GameMap.h"
#include <exception> // TODO: remove 

using namespace Common;

Chunk* const GameMap::GetData()
{
	return chunks;
}
Chunk& GameMap::GetChunk(unsigned int x, unsigned int y)
{
	if (x >= width || y >= height)
		throw std::exception("out of bounds okay.."); // TODO: make proper error
	return chunks[width * y + x];
}
unsigned int GameMap::GetWidth()
{
	return width;
}
unsigned int GameMap::GetHeight()
{
	return height;
}

GameMap::GameMap(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	chunks = new Chunk[width * height];
}
GameMap::~GameMap()
{
	delete[] chunks;
}
