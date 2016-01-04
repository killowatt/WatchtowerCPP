#include "World.h"
#include <exception> // TODO: remove 

using namespace Common;

Chunk* const World::GetData()
{
	return chunks;
}
Chunk& World::GetChunk(unsigned int x, unsigned int y)
{
	if (x >= width || y >= height)
		throw std::exception("out of bounds okay.."); // TODO: make proper error
	return chunks[width * y + x];
}
unsigned int World::GetWidth()
{
	return width;
}
unsigned int World::GetHeight()
{
	return height;
}

World::World(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	chunks = new Chunk[width * height];
}
World::~World()
{
	delete[] chunks;
}
