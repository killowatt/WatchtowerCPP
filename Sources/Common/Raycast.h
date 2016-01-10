#pragma once
#include "glm/glm.hpp"

namespace Common
{
	class Raycast
	{
		static void RaycastBlock(glm::vec3 direction, float radius, bool active);
	};
}