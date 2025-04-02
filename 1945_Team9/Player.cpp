#include "Player.h"
#include "CommonFunction.h"
#include "Missile.h"
#include "Image.h"
#include "KeyManager.h"
#include "MissileManager.h"

#include "NormalMissileManager.h"
#include "StraightMissileManager.h"
#include "HomingMissileManager.h"
#include "LaserMissileManager.h"

#include "Collider.h"
#include "CollisionManager.h"


void Player::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 200;
	size = {40, 40};
	damage = 10;
	moveSpeed = 1.0f;
	group = CollisionGroup::Player;
	type = ObjectType::Player;
	// ����
	//barrelSize = 30;
	//barrelEnd.x = pos.x;
	//barrelEnd.y = pos.y - barrelSize;
	//fireAngle = 90.0f;
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);

	image = ImageManager::GetInstance()->AddImage(
		L"player", TEXT("Image/player.bmp"), 64, 32, 2, 1, false, true, RGB(255, 0, 255));
	// �̻���
	missileSpeed = 150.0f;

	// 미사일 매니저 리스트-각 매니저에서 미사일 발사 수행

	vecMissileManager.resize((int)MissileType::MissileTypeLength);
	// normal laser straight homing
	vecMissileManager.at((int)MissileType::Normal) = (new NormalMissileManager);
	vecMissileManager.at((int)MissileType::Laser) = (new LaserMissileManager);
	vecMissileManager.at((int)MissileType::Straight) = (new StraightMissileManager);
	vecMissileManager.at((int)MissileType::Homing) = (new HomingMissileManager);



	for (iter = vecMissileManager.begin(); iter != vecMissileManager.end(); iter++)
	{
		(*iter)->SetOwner(this);
		(*iter)->Init();
		(*iter)->SetCollisionGroup(group);
	}

	Collider* collider = new Collider(this, pos);
	colliderList.push_back(collider);
	CollisionManager::GetInstance()->AddCollider(collider, CollisionGroup::Player);
}

void Player::Release()
{
	for (iter = vecMissileManager.begin(); iter != vecMissileManager.end(); iter++)
	{
		(*iter)->Release();
		delete (*iter);
	}
	vecMissileManager.clear();
}

void Player::Update()
{
	//barrelEnd.x = pos.x + barrelSize * cosf(DEG_TO_RAD(fireAngle));
	//barrelEnd.y = pos.y - barrelSize * sinf(DEG_TO_RAD(fireAngle));

	for (iter = vecMissileManager.begin(); iter != vecMissileManager.end(); iter++)
	{
		(*iter)->Update();
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
		Fire(MissileType::Normal);
	if (KeyManager::GetInstance()->IsOnceKeyDown('E'))
		Fire(MissileType::Laser);
	if (KeyManager::GetInstance()->IsOnceKeyDown('Q'))
		Fire(MissileType::Straight);
	if (KeyManager::GetInstance()->IsOnceKeyDown('R'))
		Fire(MissileType::Homing);
	
	Move();

	UpdateRectAtCenter(rc, pos);

	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Update();
	}
}

void Player::Render(HDC hdc)
{
	if (image) image->FrameRender(hdc, pos.x, pos.y, 1, 0);
	//if (missileManager) missileManager->Render(hdc);
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Render(hdc);
	}
	/*if (!vecMissileManager.empty()) missileManager->Render(hdc, false);*/
	for (iter = vecMissileManager.begin(); iter != vecMissileManager.end(); iter++)
	{
		(*iter)->Render(hdc, false);
	}
}

void Player::Move()
{
	// ���� ���� �ʱ�ȭ
	dir = { 0, 0 };

	// �Է��� ���� ���⿡ ���� dir ���� ����
	if (KeyManager::GetInstance()->IsStayKeyDown('A'))	
		dir.x = -1.0f;
	if (KeyManager::GetInstance()->IsStayKeyDown('D'))
		dir.x = 1.0f;
	if (KeyManager::GetInstance()->IsStayKeyDown('W'))
		dir.y = -1.0f;
	if (KeyManager::GetInstance()->IsStayKeyDown('S'))
		dir.y = 1.0f;

	// ���� ���� ����ȭ
	if (dir.x != 0 || dir.y != 0)
		dir.Normalize();

	// ���� �������� �̵�
	pos.x += moveSpeed * dir.x;
	pos.y += moveSpeed * dir.y;

	// ȭ�� ���� üũ
	pos.x = clamp(pos.x, (float)size.x / 2, (float)WINSIZE_X - size.x / 2);
	pos.y = clamp(pos.y, (float)size.y / 2, (float)WINSIZE_Y - size.y / 2);
}

void Player::Fire(MissileType type)
{
	switch (type)
	{
	case MissileType::Normal:
		vecMissileManager.at((int)MissileType::Normal)->Launch(pos);
		//AddMissile(this, MissileType::Normal, barrelEnd, fireAngle, missileSpeed);
		break;
	case MissileType::Laser:
		vecMissileManager.at((int)MissileType::Laser)->Launch(pos);
		//if (LaserLaunched)	return;
		//AddMissile(this, MissileType::Laser, barrelEnd, fireAngle, missileSpeed);
		//LaserLaunched = true;
		break;
	case MissileType::Straight:
		vecMissileManager.at((int)MissileType::Straight)->Launch(pos);
		//AddMissile(this, MissileType::Straight, {barrelEnd.x - 25, barrelEnd.y}, fireAngle, missileSpeed);
		//AddMissile(this, MissileType::Straight, { barrelEnd.x + 25, barrelEnd.y}, fireAngle, missileSpeed);
		break;
	case MissileType::Homing:
		vecMissileManager.at((int)MissileType::Homing)->Launch(pos);
		break;
	}
}

void Player::AddMissile(GameObject* owner, MissileType type, FPOINT pos, float angle, float speed)
{
	//Missile* missile = vecMissileManager.at(0)->AddMissile();
	//missile->AddCollider(group);
	//missile->SetOwner(this);
	//missileManager->AddMissile(missile);
}

void Player::Dead()
{
}

Player::Player()
{
}

Player::~Player()
{
}
