#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Image.h"
#include "EnemyManager.h"
#include "MissileManager.h"
#include "CollisionManager.h"
#include "Collider.h"

void Enemy::Init()
{
	pos = { 0,0 };
	moveSpeed = 50.0f;
	rushSpeed = 50.0f;
	angle = -90.0f;
	isAlive = true;
	size = { 40,40 };
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;
	elapsedMoveTime = 0.0f;
	maxMoveTime = 3.0f; 
	isRush = false;
	type = ObjectType::Enemy;
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);

	image = ImageManager::GetInstance()->AddImage(L"ufo", TEXT("Image\\ufo.bmp"), 540, 32, 10, 1, true, true, RGB(255, 0, 255));

	enemyManager = new EnemyManager();

	missileManager = new MissileManager();
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
	if (!isAlive) return;

	elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	elapsedMoveTime += TimeManager::GetInstance()->GetDeltaTime();

	if (elapsedTime > 0.1f)
	{
		elapsedTime = 0.0f;
		animationFrame++;
		if (animationFrame > image->GetMaxFrameX() - 1)	animationFrame = 0;
	}

	if (isRush == true)
	{
		Rush();
		if (missileManager)
			missileManager->Update();
	}
	else	
		Move();

	if (elapsedMoveTime > maxMoveTime)
	{
		elapsedMoveTime = 0;
		dir.x *= -1.0f;
	}
	UpdateRectAtCenter(rc, pos);

	for (auto& collider : colliderList)
	{
		if (collider)
			collider->Update();
	}
}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}
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

void Enemy::showEnemy(EnemyType type)
{
	switch (type)
	{
	case EnemyType:: Straight:
		AddEnemy(EnemyType::Straight, { 50.0f ,-20.0f }, angle, moveSpeed);
		AddEnemy(EnemyType::Straight, { 40.0f ,-30.0f }, angle, moveSpeed);
		AddEnemy(EnemyType::Straight, { 60.0f ,-30.0f }, angle, moveSpeed);
	}
}

void Enemy::AddEnemy(EnemyType type, FPOINT pos, float angle, float speed)
{
	
	enemyManager->AddEnemy(this);
}

void Enemy::Rush()
{
	pos.y += rushSpeed * TimeManager::GetInstance()->GetDeltaTime();
}

bool Enemy::IsOutofScreen()
{
	float right = pos.x + size.x / 2;
	float left = pos.x - size.x / 2;
	float top = pos.y - size.y / 2;
	float bottom = pos.y + size.y / 2;

	if (right < 0 || left > WINSIZE_X
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
