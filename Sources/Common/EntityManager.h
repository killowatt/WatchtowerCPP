#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

namespace Watchtower
{
	class EntityManager
	{
	private:
		std::vector<std::unique_ptr<Entity>> entities;
	public:
		void AddEntity(Entity* entity);

		void Update();
		void Render();

		EntityManager() { }
	};
}