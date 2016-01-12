#pragma once
#include "glm/glm.hpp"
#include "GameMap.h"

namespace Watchtower
{
	class Raycast
	{
	public: // TODO: fix all of this okay
		static glm::ivec2 chunkToUpdate;
		static GameMap* world;
		static void RaycastBlock(glm::vec3 direction, float radius,
			bool active, glm::vec3 cam, GameMap* world);
	};
}