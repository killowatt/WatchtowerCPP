#include "Chunk.h"
#include <iterator>

using namespace Graphics;

void Chunk::Update()
{
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<unsigned int> indices;
	unsigned int currentIndexBufferOffset = 0;

	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < CHUNK_DEPTH; z++)
			{
				if (!Blocks[x][y][z].Active)
				{
					continue;
				}

				bool xPositive = true;
				if (x < CHUNK_WIDTH - 1)
					xPositive = !Blocks[x + 1][y][z].Active;

				bool xNegative = true;
				if (x > 0)
					xNegative = !Blocks[x - 1][y][z].Active;

				bool yPositive = true;
				if (y < CHUNK_HEIGHT - 1)
					yPositive = !Blocks[x][y + 1][z].Active;

				bool yNegative = true;
				if (y > 0)
					yNegative = !Blocks[x][y - 1][z].Active;

				bool zPositive = true;
				if (z < CHUNK_DEPTH - 1)
					zPositive = !Blocks[x][y][z + 1].Active;

				bool zNegative = true;
				if (z > 0)
					zNegative = !Blocks[x][y][z - 1].Active;

				BlockData block = Block::GenerateBlockData(
					xPositive, xNegative,
					yPositive, yNegative,
					zPositive, zNegative, glm::ivec3(x, y, z));

				//vertices.insert(vertices.end(),
				//	make_move_iterator(block.Vertices.begin()),
				//	make_move_iterator(block.Vertices.end()));
				//normals.insert(normals.end(),
				//	make_move_iterator(block.Normals.begin()),
				//	make_move_iterator(block.Normals.end()));

				vertices.insert(vertices.end(),
					block.Vertices.begin(),
					block.Vertices.end());
				normals.insert(normals.end(),
					block.Normals.begin(),
					block.Normals.end());

				for (int i = 0; i < block.Indices.size(); i++)
				{
					indices.push_back(block.Indices[i] + currentIndexBufferOffset);
				}
				currentIndexBufferOffset += block.Vertices.size() / 3;
			}
		}
	}

	this->vertices.SetBufferData(vertices, 3, Graphics::MemoryHint::Dynamic);
	this->normals.SetBufferData(normals, 3, Graphics::MemoryHint::Dynamic);
	this->vertexArray.SetIndexBuffer(indices, Graphics::MemoryHint::Dynamic);
	this->vertexArray.AttachBuffer(this->vertices, 0);
	this->vertexArray.AttachBuffer(this->normals, 1);
}

Chunk::Chunk()
{
	//vertexArray.AttachBuffer(vertices, 0);
	//vertexArray.AttachBuffer(normals, 1);

	Blocks = new Block**[CHUNK_WIDTH];
	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		Blocks[x] = new Block*[CHUNK_HEIGHT];
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			Blocks[x][y] = new Block[CHUNK_DEPTH];
		}
	}
}
Chunk::~Chunk()
{
	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_DEPTH; y++)
		{
			delete[] Blocks[x][y];
		}
		delete[] Blocks[x];
	}
	delete[] Blocks;
}