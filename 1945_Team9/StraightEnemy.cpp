#include "StraightEnemy.h"

StraightEnemy::StraightEnemy()
{
}

StraightEnemy::~StraightEnemy()
{
}

void StraightEnemy::Init(float posX, float posY)
{
	pos = { posX, posY };
	moveSpeed = 50.0f;
	rushSpeed = 50.0f;
	angle = -90.0f;
	isAlive = true;
	size = { 40,40 }; 
	isRush = false;
	type = ObjectType::Enemy;

	image = ImageManager::GetInstance()->AddImage(L"StraightEnemy", TEXT("Image\\Enemy\\StraightEnemyPlane.bmp"), 31, 48, 1, 1, false, true, RGB(248, 0, 248));

}

void StraightEnemy::Release()
{
}

void StraightEnemy::Update()
{
	Move();

}

void StraightEnemy::Render(HDC hdc)
{
}

void StraightEnemy::ReLoad(FPOINT pos)
{
}

void StraightEnemy::Move()
{
	float time = TimeManager::GetInstance()->GetDeltaTime();
	if (pos.y > 50)
	{
		pos.x += moveSpeed * time;
		pos.y += moveSpeed * time;
	}
	

}
