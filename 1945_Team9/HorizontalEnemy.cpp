#include "HorizontalEnemy.h"
//#include "TimeManager.h"
#include "MissileManager.h"
#include "CommonFunction.h"
#include "missile.h"
#include "Image.h"

HorizontalEnemy::HorizontalEnemy()
{
}

HorizontalEnemy::~HorizontalEnemy()
{
}

void HorizontalEnemy::Init(float posX, float posY)
{
	Super::Init(posX, posY);
	//angle = 330.0f;
	dir = { 3, 1 };
	maxFireTime = 1.0f;
	//moveSpeed = 300.f;

	offsetX = 30;
	offsetY = 10;
	image = ImageManager::GetInstance()->AddImage(L"Enemy_MJ", TEXT("Image/Enemy_MJ.bmp"), 1248, 37, 26, 1, true, true, RGB(0, 128, 128));

}

void HorizontalEnemy::Release()
{
	Super::Release();
}

void HorizontalEnemy::Update()
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

	// 화면 나가면 isAlive = false;
}

void HorizontalEnemy::Render(HDC hdc)
{
	Super::Render(hdc);
	if (isAlive)
	{
		image->TestFrameRender(hdc, rc.left - offsetX, rc.top - offsetY, rc.right + offsetX, size.y + 2 * offsetY, animationFrame, 0, false);
	}
}

void HorizontalEnemy::Reset(FPOINT pos)
{
	isAlive = true;
	this->pos = pos;
	isCollision = false;
	elapsedFireTime = 0;
	isEffect = false;
	elapsedApperTime = 0;
}

void HorizontalEnemy::Move()
{
	dir.Normalize();
	pos.y += dir.y * moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
	pos.x += dir.x * moveSpeed * TimeManager::GetInstance()->GetDeltaTime();
}

void HorizontalEnemy::Fire()
{
	float angle = ::GetAngle(pos, target->GetPos());
	missileManager->AngleLaunch(pos, angle);
}
