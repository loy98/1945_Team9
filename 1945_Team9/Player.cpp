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
	moveSpeed = 0.5f;
	group = CollisionGroup::Player;
	type = ObjectType::Player;
	state = PlayerState::Idle;
	isAlive = true;
	// ����
	//barrelSize = 30;
	//barrelEnd.x = pos.x;
	//barrelEnd.y = pos.y - barrelSize;
	//fireAngle = 90.0f;
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);

	imageList[Idle] = ImageManager::GetInstance()->AddImage(
		L"player", TEXT("Image/playeridle.bmp"), 46, 32, 2, 1, false, true, RGB(255, 0, 255));
	imageList[MoveLeft] = ImageManager::GetInstance()->AddImage(
		L"PlayerMoveLeft", TEXT("Image/PlayerMoveLeft.bmp"), 161, 32, 7, 1, false, true, RGB(255, 0, 255));
	imageList[MoveRight] = ImageManager::GetInstance()->AddImage(
		L"PlayerMoveRight", TEXT("Image/PlayerMoveRight.bmp"), 161, 32, 7, 1, false, true, RGB(255, 0, 255));

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
	animIdleCurrTime += TimeManager::GetInstance()->GetDeltaTime();
	if (animIdleCurrTime > 0.2f)
	{
		idleCurrFrame++;
		animIdleCurrTime = 0;
	}
	if (idleCurrFrame >= 2)idleCurrFrame = 0;
	

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
	switch (state)
	{
	case PlayerState::Idle:
		imageList[Idle]->TestFrameRender(
			hdc, rc.left, rc.top, rc.right, size.y, idleCurrFrame, 0, false);
		break;
	case PlayerState::MoveLeft:
		imageList[MoveLeft]->TestFrameRender(
			hdc, rc.left, rc.top, rc.right, size.y, moveCurrFrame, 0, false);
		break;
	case PlayerState::MoveRight:
		imageList[MoveRight]->TestFrameRender(
			hdc, rc.left, rc.top, rc.right, size.y, moveCurrFrame, 0, false);
		break;
	}

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

void Player::LevelUp(ItemType type)
{
	switch (type)
	{
	case ItemType::Laser:
		vecMissileManager[(int)MissileType::Laser]->LevelUp();
		break;
	case ItemType::Homing:
		vecMissileManager[(int)MissileType::Homing]->LevelUp();
		break;
	case ItemType::Normal:
		vecMissileManager[(int)MissileType::Normal]->LevelUp();
		break;
	case ItemType::Straight:
		vecMissileManager[(int)MissileType::Straight]->LevelUp();
		break;
	}
}

void Player::Move()
{
	// ���� ���� �ʱ�ȭ
	dir = { 0, 0 };

	// �Է��� ���� ���⿡ ���� dir ���� ����
	if (KeyManager::GetInstance()->IsStayKeyDown('A'))
	{
		dir.x = -1.0f;
		state = PlayerState::MoveLeft;
		animMoveCurrTime += TimeManager::GetInstance()->GetDeltaTime();
		if (animMoveCurrTime > 0.05f)
		{
			if (moveCurrFrame < 6)
				moveCurrFrame++;
			animMoveCurrTime = 0;
		}

	}
	if (KeyManager::GetInstance()->IsStayKeyDown('D'))
	{
		dir.x = 1.0f;
		state = PlayerState::MoveRight;
		animMoveCurrTime += TimeManager::GetInstance()->GetDeltaTime();
		if (animMoveCurrTime > 0.05f)
		{
			if (moveCurrFrame < 6)
				moveCurrFrame++;
			animMoveCurrTime = 0;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyUp('A') || KeyManager::GetInstance()->IsOnceKeyUp('D'))
	{
		moveCurrFrame = 0;
		animMoveCurrTime = 0;
		state = PlayerState::Idle;
	}
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
