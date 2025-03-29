#include "LaserMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"
#include "Tank.h"
LaserMissile::LaserMissile(FPOINT pos)
{
	this->pos = pos;
}
LaserMissile::~LaserMissile()
{
}
void LaserMissile::Init()
{
	Super::Init();
	isActived = true;
	moveSpeed = 50.0f;
	angle = 90.0f;
	size = { 20, pos.y };
	isLaunch = false;
	elapsedlaunchTime = 3.0f;
	launchTime = 3.0f;

	rc = GetNormalRect(pos.x - size.x / 2, 0, size.x, size.y);
	controller = new LaserController();
}

void LaserMissile::Release()
{
}

void LaserMissile::Update()
{
	pos = owner->GetPos();
	UpdateNormalRect(rc, pos);
	Super::Update();
	elapsedlaunchTime += TimeManager::GetInstance()->GetDeltaTime();
	if (elapsedlaunchTime > launchTime)
	{
		elapsedlaunchTime = 0;
		isLaunch = isLaunch ? false : true;
	}
}

void LaserMissile::Render(HDC hdc)
{
	if (isLaunch)
		Super::Render(hdc);
}

void LaserMissile::Move()
{
}

void LaserMissile::LaserMissileMove()
{

}
