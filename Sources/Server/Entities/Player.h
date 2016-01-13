#pragma once
#include <Entity.h>
#include <glm/glm.hpp>

namespace Watchtower
{
	class Player : public Entity
	{
	public:
		glm::vec3 Position;
		glm::vec2 Rotation;

		bool Update();
		void Render();

		Player();
	};
}