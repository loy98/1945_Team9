#include "Tank.h"
#include "CommonFunction.h"
#include "Missile.h"
#include "Image.h"
#include "KeyManager.h"
#include "MissileManager.h"
#include "Collider.h"
void Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 200;
	size = 70;
	damage = 10;
	moveSpeed = 0.1f;
	name = "ÅÊÅ©";
	rcCollision = GetRectAtCenter(pos.x, pos.y, size, size);

	// Æ÷½Å
	barrelSize = 30;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = 90.0f;

	image = ImageManager::GetInstance()->AddImage(L"rocket", TEXT("Image/rocket.bmp"), 52, 64, true, RGB(255, 0, 255));
	//image->Init(TEXT("Image/rocket.bmp"), 52, 64, true, RGB(255, 0, 255));
	// ¹Ì»çÀÏ
	missileCount = 10;
	missileSpeed = 150.0f;

	missileManager = new MissileManager();
	missileManager->Init();

	Collider* collider = new Collider();
	collider->SetOwner(this);
	collider->SetPos(pos);
	colliderList.push_back(collider);
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
	barrelEnd.x = pos.x + barrelSize * cosf(DEG_TO_RAD(barrelAngle));
	barrelEnd.y = pos.y - barrelSize * sinf(DEG_TO_RAD(barrelAngle));

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
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Update();
	}
}

void Tank::Render(HDC hdc)
{
	// ¸öÅë
	//RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
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
	pos.x = clamp(pos.x, (float)size / 2, (float)WINSIZE_X - size / 2);
}

void Tank::Fire(MissileType type)
{
	Missile* missile = nullptr;
	int size = missileManager->GetMissileListSize();
	switch ((int)type)
	{
	case (int)MissileType::Normal:
		if (size < 8)
		{
			missile = missileManager->CreateMissile(MissileType::Normal, barrelEnd, barrelAngle, missileSpeed);
			missileManager->AddMissile(missile);
		}
		else
    			missileManager->Launch(barrelEnd);
		break;
	case (int)MissileType::Sin:
		missile = missileManager->CreateMissile(MissileType::Sin, barrelEnd, barrelAngle, missileSpeed);
		missileManager->AddMissile(missile);
		break;
	case (int)MissileType::Laser:
		if (LaserLaunched)	return;
		missile = missileManager->CreateMissile(MissileType::Laser, barrelEnd, barrelAngle, missileSpeed);
		missile->SetOwner(this);
		missileManager->AddMissile(missile);
		LaserLaunched = true;
		break;
	}
	
}

void Tank::RotateBarrel(float angle)
{
	barrelAngle += angle;
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
