#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"
void CollisionManager::Update()
{
	const vector<Collider*>& playerColliders = colliderList[(int)CollisionGroup::Player];
	const vector<Collider*>& enemyColliders = colliderList[(int)CollisionGroup::Enemy];

	for (int i = 0; i < playerColliders.size(); ++i)
	{
		for (int j = 0; j < enemyColliders.size(); ++j)
		{
			Collider* src = playerColliders[i];
			Collider* dest = enemyColliders[j];

			if (src->CheckCollision(dest))
			{
				if (src->GetOwner()->GetObjectType() == dest->GetOwner()->GetObjectType())
					continue;
				src->GetOwner()->SetIsCollision(true);
				dest->GetOwner()->SetIsCollision(true);
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* collider, CollisionGroup group)
{
	switch (group)
	{
	case CollisionGroup::Player:
		colliderList[(int)CollisionGroup::Player].push_back(collider);
		break;
	case CollisionGroup::Enemy:
		colliderList[(int)CollisionGroup::Enemy].push_back(collider);
		break;
	}
}
