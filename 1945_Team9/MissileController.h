#pragma once
#include "config.h"
class Missile;
class MissileController
{
public:
	MissileController();
	virtual ~MissileController();

	virtual void Move(Missile* missile) =0;

};

class NormalController : public MissileController
{
public:
	NormalController();
	virtual ~NormalController();

	void Move(Missile* missile) override;
};
                   
class LaserController : public MissileController
{
public:
	LaserController();
	virtual ~LaserController();

	void Move(Missile* missile) override;
	//void Move(FPOINT& pos, const float& speed, const float& angle) override;
};

class StraightController : public MissileController
{
public:
	StraightController();
	virtual ~StraightController();

	void Move(Missile* missile) override;
};

class HomingController : public MissileController
{
public:
	HomingController();
	virtual ~HomingController();

	void Move(Missile* missile) override;
};

class EnemyMissileController : public MissileController
{
public:
	EnemyMissileController();
	virtual ~EnemyMissileController();

	void Move(Missile* missile) override;
};

class BossMissileController : public MissileController
{
public:
	BossMissileController();
	virtual ~BossMissileController();

	void Move(Missile* missile) override;
};