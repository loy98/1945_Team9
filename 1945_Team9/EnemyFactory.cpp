#include "EnemyFactory.h"
#include "Enemy.h"
#include "StraightEnemy.h"

EnemyFactory::~EnemyFactory()
{
}

Enemy* EnemyFactory::CreateEnemy()
{
	return nullptr;
}

StraightEnemyFactory::~StraightEnemyFactory()
{
}

Enemy* StraightEnemyFactory::CreateEnemy(FPOINT pos, float angle, float speed)
{
	Enemy* enemy = new StraightEnemy;
	enemy->Init();
	if (enemy->GetIsAlive() == true)
	{
		enemy->SetIsAlive(true);
		enemy->SetPos(pos);
		enemy->SetAngle(angle);
		enemy->SetMoveSpeed(speed);
	}
	return enemy;
}
