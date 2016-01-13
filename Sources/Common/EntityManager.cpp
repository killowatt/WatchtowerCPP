#include "EntityManager.h"
using namespace Watchtower;

void EntityManager::AddEntity(Entity* entity)
{
	entities.push_back(std::unique_ptr<Entity>(entity));
}
void EntityManager::Update()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->Active)
		{
			bool finished = entities[i]->Update();
			if (finished)
				entities.erase(entities.begin() + i);
		}
	}
}
void EntityManager::Render()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->Visible)
			entities[i]->Render();
	}
}