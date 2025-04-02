#include "StraightEnemy.h"
#include "TimeManager.h"
#include "MissileManager.h"
#include "CommonFunction.h"
#include "Missile.h"
#include "Image.h"

StraightEnemy::StraightEnemy()
{
}

StraightEnemy::~StraightEnemy()
{
}

void StraightEnemy::Init(float posX, float posY)
{
	Super::Init(posX, posY);

	offsetX = 10;
	offsetY = 10;
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

	Fire();
}

void StraightEnemy::Render(HDC hdc)
{
	Super::Render(hdc);
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}
}

void StraightEnemy::Reset(FPOINT pos)
{
	isAlive = true;
	this->pos = pos;
	isCollision = false;
	elapsedFireTime = 0;
}

void StraightEnemy::Move()
{
	// pos.x += moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
	pos.y += moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
}

void StraightEnemy::Fire()
{
	float angle = ::GetAngle(pos, target->GetPos());
	Missile* missile = missileManager->CreateMissile(MissileType::Normal, pos, angle, moveSpeed);
	missile->AddCollider(CollisionGroup::Enemy);
	missileManager->AddMissile(missile);
}
