#pragma once
#include "config.h"
#include <memory>

class Missile;
class MissileFactory
{
public:
	MissileFactory() {}
	virtual ~MissileFactory();
	virtual Missile* CreateMissile(FPOINT pos, float angle, float speed) = 0;
	virtual Missile* CreateMissile();
};

class NormalMissileFactory : public MissileFactory
{
public:
	NormalMissileFactory() {}
	virtual ~NormalMissileFactory();

	virtual Missile* CreateMissile(FPOINT pos, float angle, float speed) override;

};

class SinMissileFactory : public MissileFactory
{
public:
	SinMissileFactory() {}
	virtual ~SinMissileFactory();

	virtual Missile* CreateMissile(FPOINT pos, float angle, float speed) override;
};

class LaserMissileFactory : public MissileFactory
{
public:
	LaserMissileFactory() {}
	virtual ~LaserMissileFactory();

	virtual Missile* CreateMissile() override;
	virtual Missile* CreateMissile(FPOINT pos, float angle, float speed) override;

};

class StraightMissileFactory : public MissileFactory
{
public:
	StraightMissileFactory() {}
	virtual ~StraightMissileFactory();

	virtual Missile* CreateMissile() override;
	virtual Missile* CreateMissile(FPOINT pos, float angle, float speed) override;
};