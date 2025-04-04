#include "DiagonalEnemy.h"
#include "TimeManager.h"
#include "MissileManager.h"
#include "CommonFunction.h"
#include "missile.h"
#include "Image.h"

//test
#include "EnemyController.h"
DiagonalEnemy::DiagonalEnemy()
{
}

DiagonalEnemy::~DiagonalEnemy()
{
}

void DiagonalEnemy::Init(float posX, float posY)
{
	Super::Init(posX, posY);
	//angle = 330.0f;
	dir = { 3, 1 };
	maxFireTime = 3.0f;
	//moveSpeed = 300.f;

	offsetX = 30;
	offsetY = 10;
	image = ImageManager::GetInstance()->AddImage(L"Enemy_JH", TEXT("Image\\Monster_JH.bmp"), 440, 40, 11, 1, true, true, RGB(0, 128, 128));
		
	//test
	controller = new DiagonalEnemyController;
}

void DiagonalEnemy::Release()
{
	Super::Release();
}

void DiagonalEnemy::Update()
{
	Super::Update();
	if (!isAlive)	return;

	if (isLeft)	dir = { 3,1 };
	else		dir = { -3,1 };
	if (elapsedFireTime < maxFireTime)
		elapsedFireTime += TimeManager::GetInstance()->GetDeltaTime();
	if (elapsedFireTime > maxFireTime)
	{
		elapsedFireTime = maxFireTime;
		//Fire();	// test
	}
}

void DiagonalEnemy::Render(HDC hdc)
{
	Super::Render(hdc);
	if (isAlive)
	{
		image->TestFrameRender(hdc, rc.left - offsetX, rc.top - offsetY, rc.right + offsetX, size.y + 2* offsetY, animationFrame, 0, false);
	}
}

void DiagonalEnemy::Reset(FPOINT pos)
{
	isAlive = true;
	this->pos = pos;
	isCollision = false;
	elapsedFireTime = 0;
	isEffect = false; 
	elapsedApperTime = 0;
}

void DiagonalEnemy::Move()
{
	dir.Normalize();
	pos.y += dir.y * moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
	pos.x += dir.x * moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
}

void DiagonalEnemy::Fire()
{
	float angle = ::GetAngle(pos, target->GetPos());
	missileManager->AngleLaunch(pos, angle);
}
