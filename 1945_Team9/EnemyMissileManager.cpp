#include "EnemyMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"

EnemyMissileManager::EnemyMissileManager()
{
}

EnemyMissileManager::~EnemyMissileManager()
{
}

void EnemyMissileManager::Init()
{
	vecMissileList.resize(5);
	missileFactory = new EnemyMissileFactory;

	for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
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
	for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	{
		(*iter)->Update();
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
	if (!vecMissileList.empty())
	{
		for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
		{
			if (!(*iter)->GetIsActived())
			{
				(*iter)->ReLoad(pos);
				break;
			}
		}
	}
}

void EnemyMissileManager::AngleLaunch(FPOINT pos, float angle)
{
	if (!vecMissileList.empty())
	{
		for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
		{
			if (!(*iter)->GetIsActived())
			{
				(*iter)->SetAngle(angle);
				(*iter)->ReLoad(pos);
				break;
			}
		}
	}
}

void EnemyMissileManager::AddMissile()
{
	vecMissileList.push_back(missileFactory->AddMissile(collisionGroup));
	vecMissileList.back()->SetOwner(owner);
}
