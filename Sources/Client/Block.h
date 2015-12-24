#pragma once
#include <glm/glm.hpp>

struct Block
{
	bool Active;
	glm::vec3 Color;

	Block(bool active = false, glm::vec3 color = glm::vec3());
};