#pragma once
#include "Singleton.h"
#include "config.h"

enum class CollisionLayer
{
	Player,
	Enemy,
	LayerLength
};

class Collider;
class CollisionManager : public Singleton<CollisionManager>
{
public:
	void Update();
	void AddCollider(Collider* collider, CollisionLayer layer);
private:
	vector<Collider*> colliderList[(int)CollisionLayer::LayerLength];
};

