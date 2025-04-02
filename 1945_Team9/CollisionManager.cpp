#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"
#include "Player.h"
#include "Item.h"
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

			if (src->GetOwner()->GetIsCollision() || dest->GetOwner()->GetIsCollision())
				continue;

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

void CollisionManager::CheckPlayerItemCollision()
{
	const vector<Collider*>& playerColliders = colliderList[(int)CollisionGroup::Player];
	const vector<Collider*>& ItemColliders = colliderList[(int)CollisionGroup::Item];

	for (int i = 0; i < playerColliders.size(); ++i)
	{
		for (int j = 0; j < ItemColliders.size(); ++j)
		{
			Collider* src = playerColliders[i];
			Collider* dest = ItemColliders[j];

			if (src->GetOwner()->GetIsCollision() || dest->GetOwner()->GetIsCollision())
				continue;

			if (src->CheckCollision(dest))
			{
				if (src->GetOwner()->GetObjectType() == ObjectType::Missile)
					continue;
				//src->GetOwner()->SetIsCollision(true);
				dest->GetOwner()->SetIsCollision(true);
				dynamic_cast<Player*>(src->GetOwner())->LevelUp(dynamic_cast<Item*>(dest->GetOwner())->GetItemType());
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
	case CollisionGroup::Item:
		colliderList[(int)CollisionGroup::Item].push_back(collider);
		break;
	}
}
