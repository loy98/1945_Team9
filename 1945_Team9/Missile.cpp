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

	if (controller)
	{
		delete controller;
		controller = nullptr;
	}
}

void Missile::Update()
{
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Update();
	}
	Move();
	//if(isActived)
	//{
	//}

	if (isActived && IsOutofScreen())
	{
		isActived = false;
		isCollision = true;
	}
	// collider Ȯ�ο�
	//if (isActived)
	//{
	//}

	// collider ������Ʈ, ����, isActive ���� ������Ʈ(isoutofscreen)
	// active�� ��쿡��. move, isActived ����. �����̻����� ��� target pos����.-�����ſ� �߰��ϴ� ��������.
}

void Missile::Render(HDC hdc, bool isFlip)
{
	// collider Ȯ�ο�
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
	//if (isActived && !(isCollision))
	{
		controller->Move(this);
	}
}

void Missile::ReLoad(FPOINT pos)		// �߻��Ѵٸ� ����.
{
	this->pos = pos;
	isActived = true;
	isCollision = false;
	isAlive = true;
	animationFrame = 0;
	//elapsedTime = 0;
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
	isAlive = true;
}

Missile::~Missile()
{
}
