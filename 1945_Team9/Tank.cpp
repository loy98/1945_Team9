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

	image = ImageManager::GetInstance()->AddImage(
		L"player", TEXT("Image/player.bmp"), 64, 32, 2, 1, false, true, RGB(255, 0, 255));
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

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
		Fire(MissileType::Normal);
	if (KeyManager::GetInstance()->IsOnceKeyDown('E'))
		Fire(MissileType::Laser);

	Move();
	UpdateRectAtCenter(rc, pos);

	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Update();
	}
}

void Tank::Render(HDC hdc)
{
	if (image) image->FrameRender(hdc, pos.x, pos.y, 1, 0);
	//if (missileManager) missileManager->Render(hdc);
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Render(hdc);
	}
	if (missileManager) missileManager->Render(hdc, false);
}

void Tank::Move()
{
	// 방향 벡터 초기화
	dir = { 0, 0 };

	// 입력을 받은 방향에 따라 dir 벡터 설정
	if (KeyManager::GetInstance()->IsStayKeyDown('A'))	
		dir.x = -1.0f;
	if (KeyManager::GetInstance()->IsStayKeyDown('D'))
		dir.x = 1.0f;
	if (KeyManager::GetInstance()->IsStayKeyDown('W'))
		dir.y = -1.0f;
	if (KeyManager::GetInstance()->IsStayKeyDown('S'))
		dir.y = 1.0f;

	// 방향 벡터 정규화
	if (dir.x != 0 || dir.y != 0)
		dir.Normalize();

	// 계산된 방향으로 이동
	pos.x += moveSpeed * dir.x;
	pos.y += moveSpeed * dir.y;

	// 화면 범위 체크
	pos.x = clamp(pos.x, (float)size.x / 2, (float)WINSIZE_X - size.x / 2);
	pos.y = clamp(pos.y, (float)size.y / 2, (float)WINSIZE_Y - size.y / 2);
}

void Tank::Fire(MissileType type)
{
	int size = missileManager->GetMissileListSize();
	switch (type)
	{
	case MissileType::Normal:
		if (size < 8)
			AddMissile(this, MissileType::Normal, barrelEnd, fireAngle, missileSpeed);
		else
        		missileManager->Launch(barrelEnd);
		break;
	case MissileType::Sin:
		AddMissile(this, MissileType::Sin, barrelEnd, fireAngle, missileSpeed);
		break;
	case MissileType::Laser:
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
