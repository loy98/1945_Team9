#include "Tank.h"
#include "CommonFunction.h"
#include "Missile.h"
#include "Image.h"
#include "KeyManager.h"
#include "MissileManager.h"
#include "Collider.h"
#include "CollisionManager.h"

void Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 200;
	size = {40, 40};
	damage = 10;
	moveSpeed = 0.1f;
	group = CollisionGroup::Player;
	type = ObjectType::Player;
	// 포신
	barrelSize = 30;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	fireAngle = 90.0f;
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);

	image = ImageManager::GetInstance()->AddImage(L"rocket", TEXT("Image/rocket.bmp"), 52, 64, true, RGB(255, 0, 255));
	// 미사일
	missileSpeed = 150.0f;

	missileManager = new MissileManager();
	missileManager->Init();

	Collider* collider = new Collider(this, pos);
	colliderList.push_back(collider);
	CollisionManager::GetInstance()->AddCollider(collider, CollisionGroup::Player);
}

void Tank::Release()
{
	if (missileManager)
	{
		missileManager->Release();
		delete missileManager;
		missileManager = nullptr;
	}
}

void Tank::Update()
{
	barrelEnd.x = pos.x + barrelSize * cosf(DEG_TO_RAD(fireAngle));
	barrelEnd.y = pos.y - barrelSize * sinf(DEG_TO_RAD(fireAngle));

	if (missileManager) missileManager->Update();

	KeyManager* km = KeyManager::GetInstance();
	if (km->IsOnceKeyDown(VK_SPACE))	
		Fire(MissileType::Normal);
	if (km->IsOnceKeyDown('E'))
		Fire(MissileType::Laser);
	if (km->IsStayKeyDown('A'))
	{
		dir.x = -1;
		Move();
	}
	if (km->IsStayKeyDown('D'))
	{
		dir.x = 1;
		Move();
	}
	UpdateRectAtCenter(rc, pos);
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Update();
	}
}

void Tank::Render(HDC hdc)
{
	if (image) image->Render(hdc, pos.x, pos.y);
	if (missileManager) missileManager->Render(hdc);
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Render(hdc);
	}
}

void Tank::Move()
{
	pos.x += moveSpeed * dir.x;
	pos.x = clamp(pos.x, (float)size.x / 2, (float)WINSIZE_X - size.x / 2);
}

void Tank::Fire(MissileType type)
{
	int size = missileManager->GetMissileListSize();
	switch ((int)type)
	{
	case (int)MissileType::Normal:
		if (size < 8)
			AddMissile(this, MissileType::Normal, barrelEnd, fireAngle, missileSpeed);
		else
    		missileManager->Launch(barrelEnd);
		break;
	case (int)MissileType::Sin:
		AddMissile(this, MissileType::Sin, barrelEnd, fireAngle, missileSpeed);
		break;
	case (int)MissileType::Laser:
		if (LaserLaunched)	return;
		AddMissile(this, MissileType::Laser, barrelEnd, fireAngle, missileSpeed);
		LaserLaunched = true;
		break;
	}
}

void Tank::AddMissile(GameObject* owner, MissileType type, FPOINT pos, float angle, float speed)
{
	Missile* missile = missileManager->CreateMissile(type, barrelEnd, fireAngle, missileSpeed);
	missile->AddCollider(group);
	missile->SetOwner(this);
	missileManager->AddMissile(missile);
}

void Tank::Dead()
{
}

Tank::Tank()
{
}

Tank::~Tank()
{
}
