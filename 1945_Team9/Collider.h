#pragma once
#include "config.h"
class GameObject;
class Collider
{
public:
	Collider();
	~Collider();

	
	void Update();
	void Render(HDC hdc);
	void Release();
	bool CheckCollision(Collider* other);
	void SetOwner(GameObject* object) { owner = object; }
	GameObject* GetOwner() { return owner; }
	void SetPos(FPOINT pos) { this->pos = pos; }

private:
	GameObject* owner;
	FPOINT pos;
	bool isCollision;
	bool showDebug = true;
};

