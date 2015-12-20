#include "Block.h"
#include <set>

void BlockData::AppendVertex(float x, float y, float z)
{
    Vertices.push_back(x);
	Vertices.push_back(y);
	Vertices.push_back(z);
}
void BlockData::AppendFaceNormal(float x, float y, float z)
{
	for (int i = 0; i < 4; i++)
	{
		Normals.push_back(x);
		Normals.push_back(y);
		Normals.push_back(z);
	}
}
void BlockData::AppendIndices()
{
	Indices.push_back(Vertices.size() / 3 - 4);
	Indices.push_back(Vertices.size() / 3 - 3);
	Indices.push_back(Vertices.size() / 3 - 2);
	Indices.push_back(Vertices.size() / 3 - 4);
	Indices.push_back(Vertices.size() / 3 - 2);
	Indices.push_back(Vertices.size() / 3 - 1);
}
BlockData Block::GenerateBlockData(bool positiveX, bool negativeX,
	bool positiveY, bool negativeY,
	bool positiveZ, bool negativeZ)
{
	BlockData blockData;

	if (positiveX) 
	{
		blockData.AppendVertex(0.5f, -0.5f, -0.5f); // We need 24 verts otherwise normals would be incorrect.
		blockData.AppendVertex(0.5f, 0.5f, -0.5f);
		blockData.AppendVertex(0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(0.5f, -0.5f, 0.5f);

		blockData.AppendFaceNormal(1, 0, 0);
		blockData.AppendIndices();
	}
	if (negativeX)
	{
		blockData.AppendVertex(-0.5f, -0.5f, -0.5f);
		blockData.AppendVertex(-0.5f, -0.5f, 0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, -0.5f);

		blockData.AppendFaceNormal(-1, 0, 0);
		blockData.AppendIndices();
	}
	if (positiveY)
	{
		blockData.AppendVertex(-0.5f, 0.5f, -0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(0.5f, 0.5f, -0.5f);

		blockData.AppendFaceNormal(0, 1, 0);
		blockData.AppendIndices();
	}
	if (negativeY)
	{
		blockData.AppendVertex(-0.5f, -0.5f, -0.5f);
		blockData.AppendVertex(0.5f, -0.5f, -0.5f);
		blockData.AppendVertex(0.5f, -0.5f, 0.5f);
		blockData.AppendVertex(-0.5f, -0.5f, 0.5f);

		blockData.AppendFaceNormal(0, -1, 0);
		blockData.AppendIndices();
	}
	if (positiveZ)
	{
		blockData.AppendVertex(-0.5f, -0.5f, 0.5f);
		blockData.AppendVertex(0.5f, -0.5f, 0.5f);
		blockData.AppendVertex(0.5f, 0.5f, 0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, 0.5f);

		blockData.AppendFaceNormal(0, 0, 1);
		blockData.AppendIndices();
	}
	if (negativeZ)
	{
		blockData.AppendVertex(-0.5f, -0.5f, -0.5f);
		blockData.AppendVertex(-0.5f, 0.5f, -0.5f);
		blockData.AppendVertex(0.5f, 0.5f, -0.5f);
		blockData.AppendVertex(0.5f, -0.5f, -0.5f);

		blockData.AppendFaceNormal(0, 0, -1);
		blockData.AppendIndices();
	}

	return blockData;
}
Block::Block(bool active, glm::vec3 color)
{
	Active = active;
	Color = color;
}