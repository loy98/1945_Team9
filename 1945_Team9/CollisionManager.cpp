#include "CollisionManager.h"

void CollisionManager::Update()
{
}

void CollisionManager::AddCollider(Collider* collider, CollisionLayer layer)
{
	switch ((int)layer)
	{
	case (int)CollisionLayer::Player:
		colliderList[(int)CollisionLayer::Player].push_back(collider);
		break;
	case (int)CollisionLayer::Enemy:
		colliderList[(int)CollisionLayer::Enemy].push_back(collider);
		break;
	}
}
