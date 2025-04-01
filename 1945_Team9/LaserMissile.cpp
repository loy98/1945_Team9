#include "LaserMissile.h"
#include "CommonFunction.h"
#include "Image.h"
#include "MissileController.h"
#include "Player.h"
#include "ImageManager.h"

LaserMissile::LaserMissile()
{
}
LaserMissile::~LaserMissile()
{
}

void LaserMissile::Init()
{
	pos = { 0,0 };
	moveSpeed = 50.0f;
	size = { 20, pos.y };
	isActived = true;
	isLaunch = false;
	elapsedlaunchTime = 3.0f;
	launchTime = 3.0f;
	missileType = MissileType::Laser;
	animationFrame = 0;
	maxAnimationFrame = 14;
	offsetX = 60;
	offsetY = 150;

	rc = GetNormalRect(pos.x - size.x / 2, 0, size.x, size.y);
	controller = new LaserController();

	image = ImageManager::GetInstance()->AddImage(
		L"laser1", L"Image\\laser1.bmp", 462, 105, 14, 1, false, true, RGB(248, 0, 248));
}

void LaserMissile::Release()
{
}

void LaserMissile::Update()
{
	if(isActived)
	{
		float launchRenderTime = launchTime / maxAnimationFrame;

		//pos = owner->GetPos();
		UpdateLaserRect(rc, pos);
		Super::Update();

		elapsedlaunchTime += TimeManager::GetInstance()->GetDeltaTime();
		if (elapsedlaunchTime > launchTime)
		{
			elapsedlaunchTime = 0;
			isLaunch = isLaunch ? false : true;
		}
		if (elapsedlaunchTime > launchRenderTime)
		{
			animationFrame++;
			if (animationFrame > image->GetMaxFrameX() - 1)	animationFrame = 0;
		}
		isCollision = isLaunch ? false : true;
	}
}

void LaserMissile::Render(HDC hdc, bool isFlip)
{
	if (isLaunch)
	{
		Super::Render(hdc, isFlip);
		
		image->TestFrameRender(hdc, pos.x - offsetX, pos.y - WINSIZE_Y, pos.x + offsetX, WINSIZE_Y + offsetY, animationFrame, 0, false);
		animationFrame++;
	}
}