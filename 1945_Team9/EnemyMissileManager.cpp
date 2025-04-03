#include "EnemyMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "CommonFunction.h"

EnemyMissileManager::EnemyMissileManager()
{
}

EnemyMissileManager::~EnemyMissileManager()
{
}

void EnemyMissileManager::Init()
{

	vecMissileList.resize(3);
	missileFactory = new EnemyMissileFactory;

	for(iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	{
		(*iter) = missileFactory->AddMissile(collisionGroup);
	}
}

void EnemyMissileManager::Release()
{
	for (auto& missile : vecMissileList)
	{
		if (missile)
		{
			missile->Release();
			delete missile;
			missile = nullptr;
		}
	}

	if (missileFactory)
	{
		delete missileFactory;
		missileFactory = nullptr;
	}
}

void EnemyMissileManager::Update()
{
	for (auto& missile : vecMissileList)
	{
		if (missile && missile->GetIsActived())
		{
			missile->SetPos(owner->GetPos());
			missile->Update();
		}
	}
}

void EnemyMissileManager::Render(HDC hdc, bool isFlip)
{
	for (auto missile : vecMissileList)
	{
		if (missile)
			missile->Render(hdc, isFlip);
	}
}

void EnemyMissileManager::Launch(FPOINT pos)
{
	FPOINT playerPos;

	for (auto missile : vecMissileList)
	{
		if (missile && !missile->GetIsActived())
		{
			playerPos = playerTarget->GetPos();

			missile->SetOwner(owner);
			missile->ReLoad(playerPos);
			break;
		}
	}

}

//void EnemyMissileManager::Launch(FPOINT pos, float angle)
//{
//	FPOINT playerPos;
//
//	for (auto missile : vecMissileList)
//	{
//		if (missile && !missile->GetIsActived())
//		{
//			playerPos = playerTarget->GetPos();
//
//			missile->SetOwner(owner);
//			missile->ReLoad(pos,angle);
//			break;
//		}
//	}
//}

void EnemyMissileManager::AddMissile()
{
	vecMissileList.push_back(missileFactory->AddMissile(collisionGroup));
	vecMissileList.back()->SetOwner(owner);
}

void EnemyMissileManager::LevelUp()
{
}
