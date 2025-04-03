#include "Boss.h"
#include "TimeManager.h"
#include "MissileManager.h"
#include "CommonFunction.h"
#include "Missile.h"
#include "Image.h"
//#include "BossMissileManager.h"

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
	/*missileManager = new BossMissileManager;
	missileManager->SetCollisionGroup(CollisionGroup::Enemy);
	missileManager->Init();*/
	//missileManager->SetOwner(this);

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

	if (fireTime < maxFireTime)
	{
		fireTime += TimeManager::GetInstance()->GetDeltaTime();
	}
	if (fireTime >= maxFireTime)
	{
		Fire();
		fireTime = 0;
	}

	Move();
}

void Boss::Render(HDC hdc)
{
	Super::Render(hdc);
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}

	missileManager->Render(hdc, false);
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
	int randNum = rand() % 2;
	FPOINT bossPos = pos;
	float angle = ::GetAngle(pos, target->GetPos());

	if (randNum == 0)
	{
		for (int i = 0; i < 36; i++)
		{
			angle = DEG_TO_RAD(i * 10.0f);

			if (angle >= DEG_TO_RAD(180.0f) && angle < DEG_TO_RAD(360.0f)) {
				missileManager->AngleLaunch(pos, angle);
			}
		}
	}
	else if (randNum == 1)
	{
		for (int i = 0; i < 36; i++)
		{
			angle = DEG_TO_RAD(i * 10.0f);
			missileManager->AngleLaunch(pos, angle);
		}

	}

}
