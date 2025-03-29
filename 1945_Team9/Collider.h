#pragma once
#include "config.h"
class GameObject;
class Collider
{
public:
	Collider();
	~Collider();

	void Update();
	bool CheckCollision(Collider& other);
	void SetOwner(GameObject* object) { owner = object; }

private:
	GameObject* owner;

};

