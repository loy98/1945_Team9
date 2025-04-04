#pragma once
#include "config.h"
class Enemy;

// enemy move °ü¸®
class EnemyController
{
public:
	EnemyController() {};
	virtual ~EnemyController();

	virtual void Move(Enemy* enemy) = 0;
};

class DiagonalEnemyController : public EnemyController
{
public:
	DiagonalEnemyController() {};
	virtual ~DiagonalEnemyController();

	virtual void Move(Enemy* enemy) override;
};

class StraightEnemyController : public EnemyController
{
public:
	StraightEnemyController() {};
	virtual ~StraightEnemyController();

	virtual void Move(Enemy* enemy) override;
};

class HorizontalEnemyController : public EnemyController
{
public:
	HorizontalEnemyController() {};
	virtual ~HorizontalEnemyController();

	virtual void Move(Enemy* enemy) override;
};