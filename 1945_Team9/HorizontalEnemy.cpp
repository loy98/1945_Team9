#include "HorizontalEnemy.h"
#include "TimeManager.h"
#include "MissileManager.h"
#include "CommonFunction.h"
#include "missile.h"
#include "Image.h"

HorizontalEnemy::HorizontalEnemy()
{
}

HorizontalEnemy::~HorizontalEnemy()
{
}

void HorizontalEnemy::Init(float posX, float posY)
{
	Super::Init(posX, posY);
	dir = { 3, 0.1 };
	maxFireTime = 1.0f;
	moveSpeed = 300.f;

	offsetX = 30;
	offsetY = 10;
	image = ImageManager::GetInstance()->AddImage(L"Enemy_MJ", TEXT("Image/Enemy_MJ.bmp"), 1248, 37, 26, 1, true, true, RGB(255, 0, 255));

	animationFrame = 0;
	elapsedFrame;
	elapsedTime;
	elapsedMoveTime;
	maxMoveTime;
	elapsedApperTime;

	isLeft = false;
}

void HorizontalEnemy::Release()
{
	Super::Release();
}

void HorizontalEnemy::Update()
{
	int animate = animationFrame;
	Super::Update();


	//if (pos.x >= ((13.0f * animationFrame) / (WINSIZE_X / 2.0f))*300)
	//	animationFrame++;
	//if (animationFrame > image->GetMaxFrameX() - 1)	animationFrame = 0;
	
	if (elapsedTime > 0.1f)
	{
		elapsedTime = 0.0f;
		animationFrame++;
		if (animationFrame > image->GetMaxFrameX() - 1)	animationFrame = image->GetMaxFrameX() - 1;
	}


	if (!isAlive)	return;

	if (isLeft)	dir = { 3,0.1 };
	else		dir = { -3,0.1 };

	if ((pos.x >= 25) && (animationFrame <= image->GetMaxFrameX() / 2))
		Fire();	// test

	if (animationFrame > image->GetMaxFrameX() / 2)
	{
		dir.x *= -1.0f;
	}

	// 화면 나가면 isAlive = false;
}

void HorizontalEnemy::Render(HDC hdc)
{
	Super::Render(hdc);
	if (isAlive)
	{
		if(isLeft)
		{
			image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0, false);
		}
		if (!isLeft)
		{
			image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0, true);
		}
	}
}

void HorizontalEnemy::Reset(FPOINT pos)
{
	isAlive = true;
	this->pos = pos;
	isCollision = false;
	elapsedFireTime = 0;
	isEffect = false;
	elapsedApperTime = 0;
}

void HorizontalEnemy::Move()
{
	dir.Normalize();
	pos.y += dir.y * moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
	pos.x += dir.x * moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
}

void HorizontalEnemy::Fire()
{
	float angle = ::GetAngle(pos, target->GetPos());
	missileManager->AngleLaunch(pos, angle);
}

int HorizontalEnemy::GetMaxFrame()
{
	return image->GetMaxFrameX();
}
