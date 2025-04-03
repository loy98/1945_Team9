#include "EnemyMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"
#include "Image.h"
//#include "Player.h"

void EnemyMissile::Init()
{
	pos = { 0,0 };
	isActived = false;
	angle = DEG_TO_RAD( -90.0f);
	size = { 20,40 };
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);
	moveSpeed = 150.0f;
	//addSpeed = 10.0f;
	animationFrame = 0;

	//missileType = MissileType::Enemy;

	controller = new EnemyMissileController;

	image = ImageManager::GetInstance()->AddImage(L"EnemyMissile", TEXT("Image\\bullet.bmp"), 21, 21, 1, 1, false, true, RGB(255, 0, 255));
}

void EnemyMissile::Release()
{
}

void EnemyMissile::Update()
{
	Super::Update();
	UpdateRectAtCenter(rc, pos);
	if (isCollision)
		isActived = false;
}

void EnemyMissile::Render(HDC hdc, bool isFlip)
{
	if (isActived)
	{
		Super::Render(hdc, isFlip);
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0, isFlip);
	}
}

