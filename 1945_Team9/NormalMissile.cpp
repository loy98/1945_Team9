#include "NormalMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"

void NormalMissile::Init()
{
	Super::Init();

	pos = { 0, 0 };
	isActived = false;
	moveSpeed = 50.0f;
	angle = 90.0f;
	size = { 20,20 };

	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);

	controller = new NormalController();
}

void NormalMissile::Release()
{
	
}

void NormalMissile::Update()
{
	if (!isActived) 
		return;
	Move();
	UpdateRectAtCenter(rc, pos);
	if (IsOutofScreen())
	{
		isActived = false;
	}
	Super::Update();
}

void NormalMissile::Render(HDC hdc)
{
	Super::Render(hdc);
}

void NormalMissile::ReLoad(FPOINT pos)
{
	this->pos = pos;
	isActived = true;
	isCollision = false;
	angle = 90.0f;
}

void NormalMissile::Move()
{
	if (isActived)
	{
		controller->Move(this);
	}
}
