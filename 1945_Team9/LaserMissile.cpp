#include "LaserMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"
#include "Tank.h"
void LaserMissile::Init()
{
	pos = { 0, 0 };
	isActived = true;
	color = RGB(255, 255, 255);
	moveSpeed = 50.0f;
	angle = 90.0f;
	size = 20;
	isLaunch = false;
	elapsedlaunchTime = 3.0f;
	launchTime = 3.0f;

	controller = new LaserController();
}

void LaserMissile::Release()
{
}

void LaserMissile::Update()
{
	pos = owner->GetPos();
	elapsedlaunchTime += TimeManager::GetInstance()->GetDeltaTime();
	if (elapsedlaunchTime > launchTime)
	{
		elapsedlaunchTime = 0;
		isLaunch = isLaunch ? false : true;
	}
}

void LaserMissile::Render(HDC hdc)
{
	//width, height ³ª´²¾ßÇÔ
	if (isLaunch)
		RenderRectAtCenter(hdc, pos.x, pos.y, 20, WINSIZE_Y* 2);
}

void LaserMissile::Move()
{
}

void LaserMissile::LaserMissileMove()
{

}
