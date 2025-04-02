#include "HomingMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"

HomingMissileManager::HomingMissileManager()
{
}

HomingMissileManager::~HomingMissileManager()
{
}

void HomingMissileManager::Init()
{
	vecvecMissileList.resize(5);
	missileFactory = new HomingMissileFactory;

	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
		{
			(*iter) = missileFactory->AddMissile(collisionGroup);
		}
	}
}

void HomingMissileManager::Release()
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
		{
			(*iter)->Release();
			delete (*iter);
			(*iter) = nullptr;
		}
		vecvecMissileList[i].clear();
	}
	vecvecMissileList.clear();
}

void HomingMissileManager::Update()
{
	for(int i = 0; i< vecvecMissileList.size(); i++)
	{
		for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
		{
			(*iter)->Update();
		}
	}
}

void HomingMissileManager::Render(HDC hdc, bool isFlip)
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
		{
			(*iter)->Render(hdc, isFlip);
		}
	}
}

void HomingMissileManager::Launch(FPOINT pos)
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
		{
			(*iter)->ReLoad(pos);
		}
	}
}

void HomingMissileManager::AddMissile()
{
	vector<Missile*> pack;
	pack.resize(2);

	for (int i = 0; i < pack.size(); i++)
	{
		pack.push_back(missileFactory->AddMissile(collisionGroup));
		pack.back()->SetOwner(owner);
	}
	vecvecMissileList.push_back(pack);
}
