#include "Missile.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"

void Missile::Init()
{
	type = ObjectType::Missile;
}

void Missile::Release()
{
}

void Missile::Update()
{
	// collider 확인용
	if (!isActived) return;
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Update();
	}
}

void Missile::Render(HDC hdc)
{
	// collider 확인용
	if (!isActived) return;
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Render(hdc);
	}
}

void Missile::AddCollider(CollisionGroup group)
{
	Collider* collider = new Collider(this, pos);
	colliderList.push_back(collider);
	CollisionManager::GetInstance()->AddCollider(collider, group);
}

void Missile::Move()
{
	
}

void Missile::ReLoad(FPOINT pos)
{
}

bool Missile::IsOutofScreen()
{
	float right = pos.x + size.x / 2;
	float left = pos.x - size.x / 2;
	float top = pos.y - size.y / 2;
	float bottom = pos.y + size.y / 2;

	if (right < 0 || left > WINSIZE_X 
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

Missile::Missile()
{
}

Missile::~Missile()
{
}
