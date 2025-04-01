#include "StraightEnemy.h"
#include "EnemyController.h"
#include "Image.h"

StraightEnemy::StraightEnemy()
{
}

StraightEnemy::~StraightEnemy()
{
}

void StraightEnemy::Init()
{
	pos = { 0.0f, 0.0f };
	moveSpeed = 50.0f;
	//rushSpeed = 50.0f;
	angle = -90.0f;
	isAlive = true;
	//size = { 40,40 }; 
	isRush = false;
	type = ObjectType::Enemy;

	image = ImageManager::GetInstance()->AddImage(L"StraightEnemy", TEXT("Image\\Enemy\\StraightEnemyPlane.bmp"), 31, 48, 1, 1, false, true, RGB(248, 0, 248));
	controller = new StraightEnemyController();
}

void StraightEnemy::Release()
{
}

void StraightEnemy::Update()
{
	Super::Update();
	Move();

	//elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	//if (elapsedTime > rushTime)
	//{
	//	int randNum = rand() % 3;
	//	Enemy* randEnemy = vecEnemys[randNum];
	//	if (randEnemy && !randEnemy->GetIsRush())
	//	{
	//		randEnemy->SetIsRush(true);
	//		EnemyManager* m = randEnemy->GetMissileManager();

	//		Enemy* enemy = m->CreateMissile(MissileType::Normal, randEnemy->GetPos(),
	//			randEnemy->GetAngle(), randEnemy->GetRushSpeed() + 50);

	//		enemy->AddCollider(CollisionGroup::Enemy);
	//		m->AddMissile(missile);
	//	}
	//	elapsedTime = 0.0f;
	//}
	// 충돌처리나면 isAlive = false

	if (isCollision == true)
	{
		isAlive = false;
	}	
}

void StraightEnemy::Render(HDC hdc)
{
	Super::Render(hdc);

	if (isAlive)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0);
	}
}

void StraightEnemy::ReLoad(FPOINT pos)
{
	this->pos = pos;
	isAlive = true;
	isCollision = false;
	angle = 90.0f;
}

void StraightEnemy::Move()
{
	if (isAlive)
	{
		controller->Move(this);
	}
}