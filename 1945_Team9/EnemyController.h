#pragma once
#include "config.h"

class Enemy;
class EnemyController
{
public :
	EnemyController();
	virtual ~EnemyController();

	virtual void Move(Enemy* enemy);
};

class StraightEnemyController : public EnemyController
{
public:
	StraightEnemyController();
	virtual ~StraightEnemyController();

	virtual void Move(Enemy* enemy);
};
