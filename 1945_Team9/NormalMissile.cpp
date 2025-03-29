#include "NormalMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"

void NormalMissile::Init()
{
	Super::Init();

	pos = { 0, 0 };
	isActived = false;
	color = RGB(255, 255, 255);
	moveSpeed = 50.0f;
	angle = 90.0f;
	size = 20;

	controller = new NormalController();
}

void NormalMissile::Release()
{
	
}

void NormalMissile::Update()
{
	Super::Update();

	if (!isActived) 
		return;
	Move();
	if (IsOutofScreen())
	{
		isActived = false;
	}
}

void NormalMissile::Render(HDC hdc)
{
	Super::Render(hdc);
	
	/*if (isActived)
	{
		RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	}*/
}

void NormalMissile::ReLoad(FPOINT pos)
{
	this->pos = pos;
	isActived = true;
	angle = 90.0f;
}

void NormalMissile::Move()
{
	if (isActived)
	{
		controller->Move(this);
	}
}
