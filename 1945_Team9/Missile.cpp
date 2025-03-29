#include "Missile.h"
#include "CommonFunction.h"
#include "Collider.h"

void Missile::Init()
{
	Collider* collider = new Collider();
	collider->SetOwner(this);
	collider->SetPos(pos);
	colliderList.push_back(collider);

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

void Missile::Move()
{
	
}

void Missile::ReLoad(FPOINT pos)
{
}

bool Missile::IsOutofScreen()
{
	float right = pos.x + size / 2;
	float left = pos.x - size / 2;
	float top = pos.y - size / 2;
	float bottom = pos.y + size / 2;

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
