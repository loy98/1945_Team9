#pragma once
#include "config.h"
class Missile;
class MissileController
{
public:
	MissileController();
	virtual ~MissileController();

	virtual void Move(Missile* missile);

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

	//void Move(FPOINT& pos, const float& speed, const float& angle) override;
};
