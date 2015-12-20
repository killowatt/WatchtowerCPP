#pragma once
#include <glm/glm.hpp>
#include <vector>

struct BlockData
{
	std::vector<float> Vertices;
	std::vector<float> Normals;
	std::vector<unsigned int> Indices;

	void AppendVertex(float x, float y, float z);
	void AppendFaceNormal(float x, float y, float z);
	void AppendIndices();
};
struct Block
{
	bool Active;
	glm::vec3 Color;

	static BlockData GenerateBlockData(bool positiveX, bool negativeX,
		bool positiveY, bool negativeY,
		bool positiveZ, bool negativeZ);

	Block(bool active = true, glm::vec3 color = glm::vec3());
};