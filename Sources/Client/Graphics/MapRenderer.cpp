#include "ChunkRenderData.h"
#include <iterator>
using namespace Client;

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
inline void AppendColor(std::vector<float>& vector, uint8_t r, uint8_t g, uint8_t b)
{
	for (int i = 0; i < 4; i++)
	{
		vector.push_back(r / 255.0f);
		vector.push_back(g / 255.0f);
		vector.push_back(b / 255.0f);
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
	std::vector<float>& colors,
	std::vector<float>& normals,
	std::vector<unsigned int>& indices,
	bool xPositive, bool xNegative,
	bool yPositive, bool yNegative,
	bool zPositive, bool zNegative,
	glm::ivec3& position, Common::Color color)
{
	if (xPositive)
	{
		AppendVertex(vertices, 0.5f, -0.5f, -0.5f, position); // We need 24 verts otherwise normals would be incorrect.
		AppendVertex(vertices, 0.5f, 0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, 0.5f, position);

		AppendColor(colors, color.R, color.G, color.B);
		AppendFaceNormal(normals, 1, 0, 0);
		AppendIndices(indices, vertices);
	}
	if (xNegative)
	{
		AppendVertex(vertices, -0.5f, -0.5f, -0.5f, position);
		AppendVertex(vertices, -0.5f, -0.5f, 0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, -0.5f, position);

		AppendColor(colors, color.R, color.G, color.B);
		AppendFaceNormal(normals, -1, 0, 0);
		AppendIndices(indices, vertices);
	}
	if (yPositive)
	{
		AppendVertex(vertices, -0.5f, 0.5f, -0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, -0.5f, position);

		AppendColor(colors, color.R, color.G, color.B);
		AppendFaceNormal(normals, 0, 1, 0);
		AppendIndices(indices, vertices);
	}
	if (yNegative)
	{
		AppendVertex(vertices, -0.5f, -0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, 0.5f, position);
		AppendVertex(vertices, -0.5f, -0.5f, 0.5f, position);

		AppendColor(colors, color.R, color.G, color.B);
		AppendFaceNormal(normals, 0, -1, 0);
		AppendIndices(indices, vertices);
	}
	if (zPositive)
	{
		AppendVertex(vertices, -0.5f, -0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, 0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, 0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, 0.5f, position);

		AppendColor(colors, color.R, color.G, color.B);
		AppendFaceNormal(normals, 0, 0, 1);
		AppendIndices(indices, vertices);
	}
	if (zNegative)
	{
		AppendVertex(vertices, -0.5f, -0.5f, -0.5f, position);
		AppendVertex(vertices, -0.5f, 0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, 0.5f, -0.5f, position);
		AppendVertex(vertices, 0.5f, -0.5f, -0.5f, position);

		AppendColor(colors, color.R, color.G, color.B);
		AppendFaceNormal(normals, 0, 0, -1);
		AppendIndices(indices, vertices);
	}
}

ChunkRenderData::ChunkRenderData()
{
}

void MapRenderer::RenderChunk::Generate(const Common::Chunk& chunk, int x, int y)
{
	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<float> normals;
	std::vector<unsigned int> indices;

	int vertexBufferSize = 0;
	int indexBufferSize = 0;

	// Calculate the size of the buffers.
	for (int x = 0; x < Common::Chunk::CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < Common::Chunk::CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < Common::Chunk::CHUNK_DEPTH; z++)
			{
				if (!chunk.GetBlock(x, y, z).Active)
				{
					continue;
				}

				bool xPositive = true;
				if (x < Common::Chunk::CHUNK_WIDTH - 1)
					xPositive = !chunk.GetBlock(x + 1, y, z).Active;

				bool xNegative = true;
				if (x > 0)
					xNegative = !chunk.GetBlock(x - 1, y, z).Active;

				bool yPositive = true;
				if (y < Common::Chunk::CHUNK_HEIGHT - 1)
					yPositive = !chunk.GetBlock(x, y + 1, z).Active;

				bool yNegative = true;
				if (y > 0)
					yNegative = !chunk.GetBlock(x, y - 1, z).Active;

				bool zPositive = true;
				if (z < Common::Chunk::CHUNK_DEPTH - 1)
					zPositive = !chunk.GetBlock(x, y, z + 1).Active;

				bool zNegative = true;
				if (z > 0)
					zNegative = !chunk.GetBlock(x, y, z - 1).Active;

				int sides = xPositive + xNegative + yPositive + yNegative + zPositive + zNegative;
				vertexBufferSize += sides * 12;
				indexBufferSize += sides * 6;
			}
		}
	}

	if (vertexBufferSize <= 0 || indexBufferSize <= 0)
	{
		return;
	}

	vertices.reserve(vertexBufferSize);
	colors.reserve(vertexBufferSize);
	normals.reserve(vertexBufferSize);
	indices.reserve(indexBufferSize);

	// Create the vertex data.
	for (int x = 0; x < Common::Chunk::CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < Common::Chunk::CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < Common::Chunk::CHUNK_DEPTH; z++)
			{
				if (!chunk.GetBlock(x, y, z).Active)
				{
					continue;
				}

				bool xPositive = true;
				if (x < Common::Chunk::CHUNK_WIDTH - 1)
					xPositive = !chunk.GetBlock(x + 1, y, z).Active;

				bool xNegative = true;
				if (x > 0)
					xNegative = !chunk.GetBlock(x - 1, y, z).Active;

				bool yPositive = true;
				if (y < Common::Chunk::CHUNK_HEIGHT - 1)
					yPositive = !chunk.GetBlock(x, y + 1, z).Active;

				bool yNegative = true;
				if (y > 0)
					yNegative = !chunk.GetBlock(x, y - 1, z).Active;

				bool zPositive = true;
				if (z < Common::Chunk::CHUNK_DEPTH - 1)
					zPositive = !chunk.GetBlock(x, y, z + 1).Active;

				bool zNegative = true;
				if (z > 0)
					zNegative = !chunk.GetBlock(x, y, z - 1).Active;

				GenerateBlockData(vertices, colors, normals, indices,
					xPositive, xNegative,
					yPositive, yNegative,
					zPositive, zNegative,
					glm::ivec3(x, y, z), chunk.GetBlock(x, y, z).Color);
			}
		}
	}

	Vertices.SetBufferData(vertices, 3, Client::MemoryHint::Dynamic);
	Colors.SetBufferData(colors, 3, Client::MemoryHint::Dynamic);
	Normals.SetBufferData(normals, 3, Client::MemoryHint::Dynamic);
	VertexArray.SetIndexBuffer(indices, Client::MemoryHint::Dynamic);
	VertexArray.AttachBuffer(Vertices, 0);
	VertexArray.AttachBuffer(Colors, 1);
	VertexArray.AttachBuffer(Normals, 2);
	Transform = glm::translate(glm::mat4(), 
		glm::vec3(x * Common::Chunk::CHUNK_WIDTH, 0, y * Common::Chunk::CHUNK_DEPTH));
}