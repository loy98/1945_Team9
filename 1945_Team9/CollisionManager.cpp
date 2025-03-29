#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"
void CollisionManager::Update()
{
	vector<Collider*>& playerColliders = colliderList[(int)CollisionLayer::Player];
	vector<Collider*>& enemyColliders = colliderList[(int)CollisionLayer::Enemy];

	for (int i = 0; i < playerColliders.size(); ++i)
	{
		for (int j = 0; j < enemyColliders.size(); ++j)
		{
			Collider* src = playerColliders[i];
			Collider* dest = enemyColliders[j];

			if (src->CheckCollision(dest))
			{
				src->GetOwner()->SetIsCollision(true);
				dest->GetOwner()->SetIsCollision(true);
			}


		}
	}

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
