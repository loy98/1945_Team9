#pragma once
#include "config.h"
#include <memory>

class Missile;
class MissileFactory
{
public:
	MissileFactory() {}
	virtual ~MissileFactory();
	Missile* AddMissile(CollisionGroup group);

private:
	virtual Missile* CreateMissile() = 0;
};

class NormalMissileFactory : public MissileFactory
{
public:
	NormalMissileFactory() {}
	virtual ~NormalMissileFactory();

private:
	virtual Missile* CreateMissile() override;

};

class LaserMissileFactory : public MissileFactory
{
public:
	LaserMissileFactory() {}
	virtual ~LaserMissileFactory();

private:
	virtual Missile* CreateMissile() override;
};

class StraightMissileFactory : public MissileFactory
{
public:
	StraightMissileFactory() {}
	virtual ~StraightMissileFactory();

private:
	virtual Missile* CreateMissile() override;
};

class HomingMissileFactory : public MissileFactory
{
public:
	HomingMissileFactory() {}
	virtual ~HomingMissileFactory();

private:
	virtual Missile* CreateMissile() override;
};

class EnemyMissileFactory : public MissileFactory
{
public:
	EnemyMissileFactory() {}
	virtual ~EnemyMissileFactory();

private:
	virtual Missile* CreateMissile() override;

};

//class BossMissileFactory : public MissileFactory
//{
//public:
//	BossMissileFactory() {}
//	virtual ~BossMissileFactory();
//
//private:
//	virtual Missile* CreateMissile() override;
//
//};

