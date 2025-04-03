#include "Enemy.h"
#include "CommonFunction.h"
#include "Player.h"
#include "Image.h"
#include "Effect.h"
#include "MissileManager.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "NormalMissileManager.h"
#include "ItemManager.h"
#include "EffectManager.h"

void Enemy::Init(float posX, float posY)
{
	pos = { posX, posY };
	moveSpeed = 150.0f;
	angle = -90.0f;
	isAlive = false;
	size = { 40,40 };
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;
	elapsedMoveTime = 0.0f;
	maxMoveTime = 3.0f; 
	isCollision = false;
	isEffect = false;

	type = ObjectType::Enemy;
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);

	//image = ImageManager::GetInstance()->AddImage(L"ufo", TEXT("Image\\ufo.bmp"), 540, 32, 10, 1, true, true, RGB(255, 0, 255));

	missileManager = new NormalMissileManager();
	missileManager->SetCollisionGroup(CollisionGroup::Enemy);
	missileManager->Init();

	Collider* collider = new Collider(this, pos);
	colliderList.push_back(collider);
	CollisionManager::GetInstance()->AddCollider(collider, CollisionGroup::Enemy);
}

void Enemy::Release()
{
	if (missileManager)
	{
		missileManager->Release();
		delete missileManager;
		missileManager = nullptr;
	}
}

void Enemy::Update()
{
	if (isCollision && !isEffect)
	{
		AddEffects();
		/*-----------적 죽으면 랜덤 아이템 생성------------*/
		int num = rand() % 200;
		int typeNum = rand() % (int)ItemType::ItemTypeLength;
		if (num < 2)
		{
			ItemManager::GetInstance()->AddItem((ItemType)typeNum, pos, { 20, 20 });
		}
		/*--------------------------------------------------*/
		isEffect = true;
	}
	if (!isAlive) return;

	elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	elapsedMoveTime += TimeManager::GetInstance()->GetDeltaTime();
	elapsedApperTime += TimeManager::GetInstance()->GetDeltaTime();

	if (elapsedTime > 0.1f)
	{
		elapsedTime = 0.0f;
		animationFrame++;
		if (animationFrame > image->GetMaxFrameX() - 1)	animationFrame = 0;
	}
	if (missileManager)
	{
		missileManager->Update();
	}
	Move();

	UpdateRectAtCenter(rc, pos);
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Update();
	}

}

void Enemy::Render(HDC hdc)
{
	if (missileManager)
	{
		missileManager->Render(hdc,true);
	}
	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Render(hdc);
	}
}

void Enemy::Move()
{
	pos.x += moveSpeed * dir.x * TimeManager::GetInstance()->GetDeltaTime();
}

void Enemy::Fire()
{
}

void Enemy::Reset(FPOINT pos)
{
	
}

void Enemy::ChangeApperSide()
{
	isLeft = !isLeft;
}

bool Enemy::IsOutofScreen()
{
	if (elapsedApperTime < 3.0f) return false;
	float right = pos.x + size.x / 2;
	float left = pos.x - size.x / 2;
	float top = pos.y - size.y / 2;
	float bottom = pos.y + size.y / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

void Enemy::AddEffects()
{
	Effect* effect1 = new Effect();
	effect1->Init(L"EnemyDie", { pos.x + 10, pos.y - 10 }, size, 30, 20);
	EffectManager::GetInstance()->AddEffect(effect1);

	Effect* effect2 = new Effect();
	effect2->Init(L"EnemyDie", { pos.x - 10, pos.y + 10 }, size, 30, 20);
	EffectManager::GetInstance()->AddEffect(effect2);

	Effect* effect3 = new Effect();
	effect3->Init(L"EnemyDie", { pos.x + 30, pos.y + 20 }, size, 30, 20);
	EffectManager::GetInstance()->AddEffect(effect3);
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
