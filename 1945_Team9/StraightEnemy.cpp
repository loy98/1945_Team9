#include "StraightEnemy.h"
#include "TimeManager.h"
#include "MissileManager.h"
#include "CommonFunction.h"
#include "Missile.h"
#include "Image.h"

#include "EnemyMissileManager.h"

StraightEnemy::StraightEnemy()
{
}

StraightEnemy::~StraightEnemy()
{
}

void StraightEnemy::Init(float posX, float posY)
{
	Super::Init(posX, posY);

	offsetX = 30;
	offsetY = 30;
	maxFireTime = 3.0f;

	image = ImageManager::GetInstance()->AddImage(L"StraightEnemy", TEXT("Image\\StraightEnemyPlane.bmp"), 31, 48, 1, 1, false, true, RGB(248, 0, 248));
}

void StraightEnemy::Release()
{
	Super::Release();
}

void StraightEnemy::Update()
{
	Super::Update();
	if (!isAlive) return;

	if (fireTime < maxFireTime)
	{
		fireTime += TimeManager::GetInstance()->GetDeltaTime();
	}
	if (fireTime > maxFireTime)
	{
		Fire();
		fireTime = 0;
	}
	
	//missileManager->Update();
}

void StraightEnemy::Render(HDC hdc)
{
	Super::Render(hdc);
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
		
	}

	//missileManager->Render(hdc, false);
}

void StraightEnemy::Reset(FPOINT pos)
{
	isAlive = true;
	this->pos = pos;
	isCollision = false;
	fireTime = 0;
	//isEffect = false;
}

void StraightEnemy::Move()
{
	// pos.x += moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
	pos.y += moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
}

void StraightEnemy::Fire()
{
	FPOINT playerPos = target->GetPos();
	float angle = ::GetAngle(pos, target->GetPos());
	missileManager->AngleLaunch(pos, angle);
	/*
	Missile* missile = missileManager->CreateMissile(MissileType::Normal, pos, angle, moveSpeed);
	missile->AddCollider(CollisionGroup::Enemy);
	missileManager->AddMissile(missile);*/
}
