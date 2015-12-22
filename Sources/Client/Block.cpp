#include "Block.h"
#include <set>

inline void BlockData::AppendVertex(float x, float y, float z)
{
	Vertices.reserve(Vertices.size() + 3);
    Vertices.push_back(x);
	Vertices.push_back(y);
	Vertices.push_back(z);
}
inline void BlockData::AppendFaceNormal(float x, float y, float z)
{
	Normals.reserve(Normals.size() + 12);
	for (int i = 0; i < 4; i++)
	{
		Normals.push_back(x);
		Normals.push_back(y);
		Normals.push_back(z);
	}
}
inline void BlockData::AppendIndices()
{
	Indices.reserve(Indices.size() + 6);
	Indices.push_back(Vertices.size() / 3 - 4);
	Indices.push_back(Vertices.size() / 3 - 3);
	Indices.push_back(Vertices.size() / 3 - 2);
	Indices.push_back(Vertices.size() / 3 - 4);
	Indices.push_back(Vertices.size() / 3 - 2);
	Indices.push_back(Vertices.size() / 3 - 1);
}
BlockData Block::GenerateBlockData(bool xPositive, bool xNegative,
	bool yPositive, bool yNegative,
	bool zPositive, bool zNegative, glm::ivec3& position)
{
	BlockData blockData;

	if (xPositive) 
	{
		blockData.AppendVertex(0.5f, -0.5f, -0.5f); // We need 24 verts otherwise normals would be incorrect.
		blockData.AppendVertex(0.5f, 0.5f, -0.5f);
		blockData.AppendVertex(0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(0.5f, -0.5f, 0.5f);

		blockData.AppendFaceNormal(1, 0, 0);
		blockData.AppendIndices();
	}
	if (xNegative)
	{
		blockData.AppendVertex(-0.5f, -0.5f, -0.5f);
		blockData.AppendVertex(-0.5f, -0.5f, 0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, -0.5f);

		blockData.AppendFaceNormal(-1, 0, 0);
		blockData.AppendIndices();
	}
	if (yPositive)
	{
		blockData.AppendVertex(-0.5f, 0.5f, -0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(0.5f, 0.5f, -0.5f);

		blockData.AppendFaceNormal(0, 1, 0);
		blockData.AppendIndices();
	}
	if (yNegative)
	{
		blockData.AppendVertex(-0.5f, -0.5f, -0.5f);
		blockData.AppendVertex(0.5f, -0.5f, -0.5f);
		blockData.AppendVertex(0.5f, -0.5f, 0.5f);
		blockData.AppendVertex(-0.5f, -0.5f, 0.5f);

		blockData.AppendFaceNormal(0, -1, 0);
		blockData.AppendIndices();
	}
	if (zPositive)
	{
		blockData.AppendVertex(-0.5f, -0.5f, 0.5f);
		blockData.AppendVertex(0.5f, -0.5f, 0.5f);
		blockData.AppendVertex(0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, 0.5f);

		blockData.AppendFaceNormal(0, 0, 1);
		blockData.AppendIndices();
	}
	if (zNegative)
	{
		blockData.AppendVertex(-0.5f, -0.5f, -0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, -0.5f);
		blockData.AppendVertex(0.5f, 0.5f, -0.5f);
		blockData.AppendVertex(0.5f, -0.5f, -0.5f);

		blockData.AppendFaceNormal(0, 0, -1);
		blockData.AppendIndices();
	}

	for (int i = 0; i < blockData.Vertices.size(); i += 3)
	{
		blockData.Vertices[i] += position.x + 0.5f;
		blockData.Vertices[i + 1] += position.y + 0.5f;
		blockData.Vertices[i + 2] += position.z + 0.5f;
	}

	return blockData;
}
Block::Block(bool active, glm::vec3 color)
{
	Active = active;
	Color = color;
}