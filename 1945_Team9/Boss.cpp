#include "Boss.h"
#include "TimeManager.h"
#include "MissileManager.h"
#include "CommonFunction.h"
#include "Missile.h"
#include "Image.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::Init(float posX, float posY)
{
	Super::Init(posX, posY);

	moveSpeed = 50.0f;
	maxFireTime = 3.0f;
	image = ImageManager::GetInstance()->AddImage(L"BossEnemy", TEXT("Image\\BOSS.bmp"), 2832, 136, 16, 1, false, true, RGB(255, 0, 255));
}

void Boss::Release()
{
	Super::Release();
}

void Boss::Update()
{
	Super::Update();
	if (!isAlive) return;

	Move();

	if (fireTime < maxFireTime)
	{
		fireTime += TimeManager::GetInstance()->GetDeltaTime();
	}
	if (fireTime > maxFireTime)
	{
		Fire();
		fireTime = 0;
	}
}

void Boss::Render(HDC hdc)
{
	Super::Render(hdc);
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}
}

void Boss::Reset(FPOINT pos)
{
	isAlive = true;
	this->pos = pos;
	isCollision = false;
	fireTime = 0;
}

void Boss::Move()
{
	if (pos.y < 300)
	{
		pos.y += moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
	}
}
	

void Boss::Fire()
{
	/*float angle = ::GetAngle(pos, target->GetPos());
	Missile* missile = missileManager->CreateMissile(MissileType::Normal, pos, angle, moveSpeed);
	missile->AddCollider(CollisionGroup::Enemy);
	missileManager->AddMissile(missile);*/
}
