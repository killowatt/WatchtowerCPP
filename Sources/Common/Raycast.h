#pragma once
#include "glm/glm.hpp"
#include "GameMap.h"

namespace Common
{
	class Raycast
	{
	public:
		static glm::ivec2 chunkToUpdate;
		static Common::GameMap* world;
		static void RaycastBlock(glm::vec3 direction, float radius,
			bool active, glm::vec3 cam, Common::GameMap* world);
	};
}