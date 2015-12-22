#pragma once
#include <glm/glm.hpp>
#include <vector>

struct BlockData
{
	std::vector<float> Vertices;
	std::vector<float> Normals;
	std::vector<unsigned int> Indices;

	inline void AppendVertex(float x, float y, float z);
	inline void AppendFaceNormal(float x, float y, float z);
	inline void AppendIndices();
};
struct Block
{
	bool Active;
	glm::vec3 Color;

	static BlockData GenerateBlockData(bool xPositive, bool xNegative,
		bool yPositive, bool yNegative,
		bool zPositive, bool zNegative, glm::ivec3& position);

	Block(bool active = true, glm::vec3 color = glm::vec3());
};