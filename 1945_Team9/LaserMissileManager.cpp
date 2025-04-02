#include "LaserMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"

LaserMissileManager::LaserMissileManager()
{
}

LaserMissileManager::~LaserMissileManager()
{
}

void LaserMissileManager::Init()
{
	vecMissileList.resize(1);
	missileFactory = new LaserMissileFactory;

	for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	{
		(*iter) = missileFactory->AddMissile(collisionGroup);
	}
}

void LaserMissileManager::Release()
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

	//for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	//{
	//	(*iter)->Release();
	//}
}

void LaserMissileManager::Update()
{
	for (auto& missile : vecMissileList)
	{
		if (missile && missile->GetIsActived())
		{
			missile->SetPos(owner->GetPos());
			missile->Update();
		}
	}

	//for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	//{
	//	(*iter)->Update();
	//}
}

void LaserMissileManager::Render(HDC hdc, bool isFlip)
{
	for (auto missile : vecMissileList)
	{
		if (missile)
			missile->Render(hdc, isFlip);
	}
}

void LaserMissileManager::Launch(FPOINT pos)
{
	for (auto missile : vecMissileList)
	{
		if (missile && !missile->GetIsActived())
		{
			missile->ReLoad(pos);
			break;
		}
	}

	/*for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	{
		if (!(*iter)->GetIsActived())
		{
			(*iter)->ReLoad(pos);
			break;
		}
	}*/
}

void LaserMissileManager::AddMissile()
{
	vecMissileList.push_back(missileFactory->AddMissile(collisionGroup));
	vecMissileList.back()->SetOwner(owner);
}

void LaserMissileManager::LevelUp()
{
}
