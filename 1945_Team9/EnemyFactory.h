#pragma once
#include "config.h"
#include <memory>

class Enemy;
class EnemyFactory
{
public : 
	EnemyFactory() {}
	virtual ~EnemyFactory();
	virtual Enemy* CreateEnemy(FPOINT pos, float angle, float speed) = 0;
	virtual Enemy* CreateEnemy();
};

class StraightEnemyFactory : public EnemyFactory
{
public : 
	StraightEnemyFactory() {}
	virtual ~StraightEnemyFactory();

	virtual Enemy* CreateEnemy(FPOINT pos, float angle, float speed) override;
};
