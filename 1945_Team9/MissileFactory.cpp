#include "MissileFactory.h"
#include "Missile.h"
#include "NormalMissile.h"
#include "LaserMissile.h"
#include "StraightMissile.h"


MissileFactory::~MissileFactory()
{
}

Missile* MissileFactory::CreateMissile()
{
	return nullptr;
}

NormalMissileFactory::~NormalMissileFactory()
{
}

Missile* NormalMissileFactory::CreateMissile(FPOINT pos, float angle, float speed)
{
	Missile* missile = new NormalMissile();
	missile->Init();
	if (missile->GetIsActived() == false)
	{
		missile->SetIsActived(true);
		missile->SetPos(pos);
		missile->SetAngle(angle);
		missile->SetMoveSpeed(speed);
	}
	return missile;
}

SinMissileFactory::~SinMissileFactory()
{
}

Missile* SinMissileFactory::CreateMissile(FPOINT pos, float angle, float speed)
{
	return nullptr;
}

LaserMissileFactory::~LaserMissileFactory()
{
}

Missile* LaserMissileFactory::CreateMissile()
{
	return nullptr;
}

Missile* LaserMissileFactory::CreateMissile(FPOINT pos, float angle, float speed)
{
	Missile* missile = new LaserMissile(pos);
	missile->Init();
	missile->SetPos(pos);
	return missile;
}

StraightMissileFactory::~StraightMissileFactory()
{
}

Missile* StraightMissileFactory::CreateMissile()
{
	return nullptr;
}

Missile* StraightMissileFactory::CreateMissile(FPOINT pos, float angle, float speed)
{
	Missile* missile = new StraightMissile();
	missile->Init();
	if (missile->GetIsActived() == false)
	{
		missile->SetIsActived(true);
		missile->SetPos(pos);
		missile->SetAngle(angle);
		missile->SetMoveSpeed(speed);
	}
	return missile;
}
