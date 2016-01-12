#include "EntityManager.h"
using namespace Watchtower;

void EntityManager::AddEntity(Entity* entity)
{
	entities.push_back(std::unique_ptr<Entity>(entity));
}

void EntityManager::Update()
{
}
void EntityManager::Render()
{
}