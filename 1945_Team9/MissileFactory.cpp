#include "MissileFactory.h"
#include "Missile.h"
#include "NormalMissile.h"
#include "LaserMissile.h"
#include "StraightMissile.h"
#include "HomingMissile.h"
#include "Collider.h"
#include "EnemyMissile.h"

MissileFactory::~MissileFactory()
{
}

Missile* MissileFactory::AddMissile(CollisionGroup group)
{
	vector<Missile*> pack;
	pack.resize(2);

	Missile* missile = CreateMissile();
	missile->Init();
	missile->AddCollider(missile, group);
	return missile;
}

NormalMissileFactory::~NormalMissileFactory()
{
}

Missile* NormalMissileFactory::CreateMissile()
{
	return new NormalMissile();
}

LaserMissileFactory::~LaserMissileFactory()
{
}

Missile* LaserMissileFactory::CreateMissile()
{
	return new LaserMissile();
}

StraightMissileFactory::~StraightMissileFactory()
{
}

Missile* StraightMissileFactory::CreateMissile()
{
	return new StraightMissile();
}

//Missile* StraightMissileFactory::CreateMissile(FPOINT pos, float angle, float speed)
//{
//	Missile* missile = new StraightMissile();
//	missile->Init();
//	if (missile->GetIsActived() == false)
//	{
//		missile->SetIsActived(true);
//		missile->SetPos(pos);
//		missile->SetAngle(angle);
//		missile->SetMoveSpeed(speed);
//	}
//	return missile;
//}

HomingMissileFactory::~HomingMissileFactory()
{
}

Missile* HomingMissileFactory::CreateMissile()
{
	return new HomingMissile();
}

EnemyMissileFactory::~EnemyMissileFactory()
{
}

Missile* EnemyMissileFactory::CreateMissile()
{
	return new EnemyMissile;
}
