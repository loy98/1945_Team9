#include "Missile.h"
#include "CommonFunction.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "MissileController.h"

void Missile::Release()
{
	for (auto& collider : colliderList)	// gameobject
	{
		if (collider)
		{
			collider->Release();
			delete collider;
			collider = nullptr;
		}
	}
}

void Missile::Update()
{
	if(isActived)
	{
		Move();
	}

	if (isActived && IsOutofScreen())
	{
		isActived = false;
	}
	// collider 확인용
	if (isActived)
	{
		for (auto& collider : colliderList)
		{
			if (collider)
				collider->Update();
		}
	}

	// collider 업데이트, 무브, isActive 상태 업데이트(isoutofscreen)
	// active일 경우에만. move, isActived 상태. 유도미사일의 경우 target pos까지.-기존거에 추가하는 방향으로.
}

void Missile::Render(HDC hdc, bool isFlip)
{
	// collider 확인용
	if (isActived)
	{
		for (auto& collider : colliderList)
		{
			if (collider)
				collider->Render(hdc);
		}
	}
}

void Missile::AddCollider(Missile* missile, CollisionGroup group)
{
	Collider* collider = new Collider(missile, missile->pos);
	colliderList.push_back(collider);
	CollisionManager::GetInstance()->AddCollider(collider, group);
}

void Missile::Move()
{
	if(isActived)
	{
		controller->Move(this);
	}
}

void Missile::ReLoad(FPOINT pos)		// 발사한다면 세팅.
{
	this->pos = pos;
	isActived = true;
	isCollision = false;
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
	type = ObjectType::Missile;
}

Missile::~Missile()
{
}
