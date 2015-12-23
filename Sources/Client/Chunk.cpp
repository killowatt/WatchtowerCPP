#include "Chunk.h"
#include <iterator>

using namespace Graphics;

inline void AppendVertex(std::vector<float>& vector, float x, float y, float z, glm::ivec3& position)
{
	vector.push_back(x + position.x + 0.5f);
	vector.push_back(y + position.y + 0.5f);
	vector.push_back(z + position.z + 0.5f);
}
inline void AppendFaceNormal(std::vector<float>& vector, float x, float y, float z)
{
	for (int i = 0; i < 4; i++)
	{
		vector.push_back(x);
		vector.push_back(y);
		vector.push_back(z);
	}
}
inline void AppendIndices(std::vector<unsigned int>& indices, std::vector<float>& vertices)
{
	indices.push_back(vertices.size() / 3 - 4);
	indices.push_back(vertices.size() / 3 - 3);
	indices.push_back(vertices.size() / 3 - 2);
	indices.push_back(vertices.size() / 3 - 4);
	indices.push_back(vertices.size() / 3 - 2);
	indices.push_back(vertices.size() / 3 - 1);
}
void GenerateBlockData(
	std::vector<float>& vertices,
	std::vector<float>& normals,
	std::vector<unsigned int>& indices,
	bool xPositive, bool xNegative,
	bool yPositive, bool yNegative,
	bool zPositive, bool zNegative,
	glm::ivec3& position)
{
	//int sidesTotal = xPositive + xNegative + yPositive + yNegative + zPositive + zNegative;
	//int reserve = sidesTotal * (12);
	//vertices.reserve(vertices.size() + reserve);
	//normals.reserve(normals.size() + reserve);
	//indices.reserve(indices.size() + sidesTotal * 6);

	if (xPositive)
	{
		AppendVertex(vertices, 0.5f, -0.5f, -0.5f, position); // We need 24 verts otherwise normals would be incorrect.
		AppendVertex(vertices, 0.5f, 0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, 0.5f, position);

		AppendFaceNormal(normals, 1, 0, 0);
		AppendIndices(indices, vertices);
	}
	if (xNegative)
	{
		AppendVertex(vertices, -0.5f, -0.5f, -0.5f, position);
		AppendVertex(vertices, -0.5f, -0.5f, 0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, -0.5f, position);

		AppendFaceNormal(normals, -1, 0, 0);
		AppendIndices(indices, vertices);
	}
	if (yPositive)
	{
		AppendVertex(vertices, -0.5f, 0.5f, -0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, -0.5f, position);

		AppendFaceNormal(normals, 0, 1, 0);
		AppendIndices(indices, vertices);
	}
	if (yNegative)
	{
		AppendVertex(vertices, -0.5f, -0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, 0.5f, position);
		AppendVertex(vertices, -0.5f, -0.5f, 0.5f, position);

		AppendFaceNormal(normals, 0, -1, 0);
		AppendIndices(indices, vertices);
	}
	if (zPositive)
	{
		AppendVertex(vertices, -0.5f, -0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, 0.5f, position);

		AppendFaceNormal(normals, 0, 0, 1);
		AppendIndices(indices, vertices);
	}
	if (zNegative)
	{
		AppendVertex(vertices, -0.5f, -0.5f, -0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, -0.5f, position);

		AppendFaceNormal(normals, 0, 0, -1);
		AppendIndices(indices, vertices);
	}
}
void Chunk::Update()
{
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<unsigned int> indices;

	int vertexBufferSize = 0;
	int indexBufferSize = 0;

	// Calculate the size of the buffers.
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

				int sides = xPositive + xNegative + yPositive + yNegative + zPositive + zNegative;
				vertexBufferSize += sides * 12;
				indexBufferSize += sides * 6;
			}
		}
	}

	vertices.reserve(vertexBufferSize);
	normals.reserve(vertexBufferSize);
	indices.reserve(indexBufferSize);

	// Create the vertex data.
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

				GenerateBlockData(vertices, normals, indices,
					xPositive, xNegative,
					yPositive, yNegative,
					zPositive, zNegative, glm::ivec3(x, y, z));
			}
		}
	}

	Vertices.SetBufferData(vertices, 3, Graphics::MemoryHint::Dynamic);
	Normals.SetBufferData(normals, 3, Graphics::MemoryHint::Dynamic);
	VertexArray.SetIndexBuffer(indices, Graphics::MemoryHint::Dynamic);
	VertexArray.AttachBuffer(Vertices, 0);
	VertexArray.AttachBuffer(Normals, 1);
}

#pragma region oldUpdate
//void Chunk::Update()
//{
//	std::vector<float> vertices;
//	std::vector<float> normals;
//	std::vector<unsigned int> indices;
//	unsigned int currentIndexBufferOffset = 0;
//
//	for (int x = 0; x < CHUNK_WIDTH; x++)
//	{
//		for (int y = 0; y < CHUNK_HEIGHT; y++)
//		{
//			for (int z = 0; z < CHUNK_DEPTH; z++)
//			{
//				if (!Blocks[x][y][z].Active)
//				{
//					continue;
//				}
//
//				bool xPositive = true;
//				if (x < CHUNK_WIDTH - 1)
//					xPositive = !Blocks[x + 1][y][z].Active;
//
//				bool xNegative = true;
//				if (x > 0)
//					xNegative = !Blocks[x - 1][y][z].Active;
//
//				bool yPositive = true;
//				if (y < CHUNK_HEIGHT - 1)
//					yPositive = !Blocks[x][y + 1][z].Active;
//
//				bool yNegative = true;
//				if (y > 0)
//					yNegative = !Blocks[x][y - 1][z].Active;
//
//				bool zPositive = true;
//				if (z < CHUNK_DEPTH - 1)
//					zPositive = !Blocks[x][y][z + 1].Active;
//
//				bool zNegative = true;
//				if (z > 0)
//					zNegative = !Blocks[x][y][z - 1].Active;
//
//				BlockData block = Block::GenerateBlockData(
//					xPositive, xNegative,
//					yPositive, yNegative,
//					zPositive, zNegative, glm::ivec3(x, y, z));
//
//				//vertices.insert(vertices.end(),
//				//	make_move_iterator(block.Vertices.begin()),
//				//	make_move_iterator(block.Vertices.end()));
//				//normals.insert(normals.end(),
//				//	make_move_iterator(block.Normals.begin()),
//				//	make_move_iterator(block.Normals.end()));
//
//				vertices.insert(vertices.end(),
//					block.Vertices.begin(),
//					block.Vertices.end());
//				normals.insert(normals.end(),
//					block.Normals.begin(),
//					block.Normals.end());
//
//				for (int i = 0; i < block.Indices.size(); i++)
//				{
//					indices.push_back(block.Indices[i] + currentIndexBufferOffset);
//				}
//				currentIndexBufferOffset += block.Vertices.size() / 3;
//			}
//		}
//	}
//
//	this->vertices.SetBufferData(vertices, 3, Graphics::MemoryHint::Dynamic);
//	this->normals.SetBufferData(normals, 3, Graphics::MemoryHint::Dynamic);
//	this->vertexArray.SetIndexBuffer(indices, Graphics::MemoryHint::Dynamic);
//	this->vertexArray.AttachBuffer(this->vertices, 0);
//	this->vertexArray.AttachBuffer(this->normals, 1);
//}
#pragma endregion

Chunk::Chunk()
{
}
Chunk::~Chunk()
{
}