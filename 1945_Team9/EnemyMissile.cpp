#include "EnemyMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"
#include "Image.h"
#include "Player.h"


EnemyMissile::EnemyMissile()
{
}

EnemyMissile::~EnemyMissile()
{
}

void EnemyMissile::Init()
{
	pos = { 0,0 };
	isActived = false;
	angle = 90.0f;
	size = { 20,40 };
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);
	moveSpeed = 80.0f;
	addSpeed = 10.0f;
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;
	elapsedMoveTime = 0.0f;
	maxMoveTime = 3.0f;
	missileType = MissileType::Enemy;

	controller = new EnemyMissileController;

	image = ImageManager::GetInstance()->AddImage(L"EnemyMissile", TEXT("Image\\bullet.bmp"), 21, 21, 1, 1, false, true, RGB(255, 0, 255));
}

void EnemyMissile::Release()
{
}

void EnemyMissile::Update()
{
	elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	elapsedMoveTime += TimeManager::GetInstance()->GetDeltaTime();

	if (isActived)
	{
		if (elapsedTime > 0.1f)
		{
			elapsedTime = 0.0f;
			animationFrame++;
			if (animationFrame > image->GetMaxFrameX() - 1)	animationFrame = image->GetMaxFrameX() - 1;
		}
	}	

	Super::Update();

	if (IsOutofScreen() == true)
	{
		isActived = false;
	}

	UpdateRectAtCenter(rc, pos);
}

void EnemyMissile::Render(HDC hdc, bool isFlip)
{
	Super::Render(hdc, isFlip);

	if (isActived)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0, isFlip);
	}
}

