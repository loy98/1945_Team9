#pragma once
#include "config.h"
#include "GameObject.h"
class Collider : public GameObject
{
public:
	Collider(GameObject* owner, FPOINT pos);
	virtual ~Collider();
	
	void Update();
	void Render(HDC hdc);
	void Release();
	bool CheckCollision(Collider* other);
	void SetOwner(GameObject* object) { owner = object; }
	GameObject* GetOwner() { return owner; }
	void SetPos(FPOINT pos) { this->pos = pos; }
	FPOINT GetPos() { return pos; }
	RECT GetRect() { return rc; }
	bool GetIsCollision() { return isCollision; }


private:
	GameObject* owner;
	FPOINT pos;
	bool isCollision;
	bool showDebug = true;
	HPEN myPen{};
	HPEN oldPen{};
	RECT rc;
};

