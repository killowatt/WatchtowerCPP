#include "World.h"
#include <glm/gtc/matrix_transform.hpp>

Chunk& World::GetChunk(unsigned int x, unsigned int y)
{
	if (x > width || y > height)
		throw std::exception("out of bounds okay.."); // TODO: make proper error
	return chunks[width * y + x];
}
void World::Update()
{
	for (int i = 0; i < width * height; i++)
	{
		chunks[i].Update();
	}
}

World::World(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	chunks = new Chunk[width * height];
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			GetChunk(x, y).Transform = glm::translate(glm::mat4(),
				glm::vec3(x * Chunk::CHUNK_WIDTH, 0, y * Chunk::CHUNK_DEPTH));
		}
	}
}
World::~World()
{
	delete[] chunks;
}