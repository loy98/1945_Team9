#include "NormalMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"
#include "Image.h"

void NormalMissile::Init()
{
	pos = { 0, 0 };
	isActived = false;
	color = RGB(255, 255, 255);
	moveSpeed = 50.0f;
	angle = 90.0f;
	size = 20;
	animationFrame = 0;

	image = ImageManager::GetInstance()->AddImage(L"1945bullet", TEXT("Image\\1945bulletTest.bmp"), 33, 33, 1, 1, false,true, RGB(248, 0, 248));
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
	if (IsOutofScreen())
	{
		isActived = false;
	}
}

void NormalMissile::Render(HDC hdc, bool isFlip)
{
	if (isActived)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0, isFlip);
		//RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	}
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
