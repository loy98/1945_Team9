#include "BossMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"

BossMissileManager::BossMissileManager()
{
}

BossMissileManager::~BossMissileManager()
{
}

void BossMissileManager::Init()
{
	vecMissileList.resize(20);
	missileFactory = new BossMissileFactory;

	for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	{
		(*iter) = missileFactory->AddMissile(collisionGroup);
	}
}

void BossMissileManager::Release()
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

void BossMissileManager::Update()
{
	for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	{
		(*iter)->Update();
	}
}

void BossMissileManager::Render(HDC hdc, bool isFlip)
{
	for (auto missile : vecMissileList)
	{
		if (missile)
			missile->Render(hdc, isFlip);
	}
}

void BossMissileManager::Launch(FPOINT pos)
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

void BossMissileManager::AngleLaunch(FPOINT pos, float angle)
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

void BossMissileManager::AddMissile()
{
	vecMissileList.push_back(missileFactory->AddMissile(collisionGroup));
	vecMissileList.back()->SetOwner(owner);
}

void BossMissileManager::LevelUp()
{
}
