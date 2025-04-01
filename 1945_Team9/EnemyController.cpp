#include "EnemyController.h"
#include "Enemy.h"

EnemyController::EnemyController()
{
}

EnemyController::~EnemyController()
{
}

void EnemyController::Move(Enemy* enemy)
{
}

StraightEnemyController::StraightEnemyController()
{
}

StraightEnemyController::~StraightEnemyController()
{
}

void StraightEnemyController::Move(Enemy* enemy)
{
	float time = TimeManager::GetInstance()->GetDeltaTime();
	FPOINT pos = enemy->GetPos();
	float moveSpeed = enemy->GetMoveSpeed();
	float angle = enemy->GetAngle();

	if (pos.y <= 50)
	{
		pos.x += moveSpeed * time;
		pos.y += moveSpeed * time;
	}
	else
	{
		pos.x = pos.x;
		pos.y = pos.y;
	}

	enemy->SetMoveSpeed(moveSpeed);
	enemy->SetPos(pos);

}
