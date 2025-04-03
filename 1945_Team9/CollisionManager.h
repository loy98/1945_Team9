#pragma once
#include "Singleton.h"
#include "config.h"

class Collider;
class CollisionManager : public Singleton<CollisionManager>
{
public:
	void Update();
	void Release();
	void CheckPlayerItemCollision();
	void AddCollider(Collider* collider, CollisionGroup layer);
private:
	vector<Collider*> colliderList[(int)CollisionGroup::GroupLength];
};

