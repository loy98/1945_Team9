#include "BossMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"
#include "Image.h"

void BossMissile::Init()
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
	missileType = MissileType::Normal;

	image = ImageManager::GetInstance()->AddImage(L"EnemyMissile", TEXT("Image\\bullet.bmp"), 21, 21, 1, 1, false, true, RGB(255, 0, 255));

	controller = new BossMissileController();
}

void BossMissile::Release()
{
}

void BossMissile::Update()
{
	Super::Update();

	elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	elapsedMoveTime += TimeManager::GetInstance()->GetDeltaTime();

	if (isActived)
	{
		//pos.y += moveSpeed * TimeManager::GetInstance()->GetDeltaTime(); // 직접 이동
	

		if (elapsedTime > 0.1f)
		{
			elapsedTime = 0.0f;
			animationFrame++;
			if (animationFrame > image->GetMaxFrameX() - 1)	animationFrame = image->GetMaxFrameX() - 1;
		}
	}
		
	if (IsOutofScreen() == true)
	{
		isActived = false;
	}

	UpdateRectAtCenter(rc, pos);
}

void BossMissile::Render(HDC hdc, bool isFlip)
{
	if (isActived)
	{
		Super::Render(hdc, isFlip);
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0, isFlip);
	}
}

BossMissile::BossMissile()
{
}

BossMissile::~BossMissile()
{
}
