#pragma once
#include "config.h"
#include <memory>

class Missile;
class MissileFactory
{
public:
	MissileFactory() {}
	virtual ~MissileFactory();
	Missile* AddMissile();

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

class SinMissileFactory : public MissileFactory
{
public:
	SinMissileFactory() {}
	virtual ~SinMissileFactory();

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