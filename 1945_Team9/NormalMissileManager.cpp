#include "NormalMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"

NormalMissileManager::NormalMissileManager()
{
}

NormalMissileManager::~NormalMissileManager()
{
}

void NormalMissileManager::Init()
{
	vecMissileList.resize(5);
	missileFactory = new NormalMissileFactory;

	for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	{
		(*iter) = missileFactory->AddMissile();
	}
}

void NormalMissileManager::Release()
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
	//vecMissileList.clear();
}

void NormalMissileManager::Update()
{
	for (iter = vecMissileList.begin(); iter != vecMissileList.end(); iter++)
	{
		(*iter)->Update();
	}
}

void NormalMissileManager::Render(HDC hdc, bool isFlip)
{
	for (auto missile : vecMissileList)
	{
		if (missile)
			missile->Render(hdc, isFlip);
	}
}

void NormalMissileManager::Launch(FPOINT pos)
{
	// ÇÑ ¹ß¸¸ ½ô.
	if(!vecMissileList.empty())
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

void NormalMissileManager::AddMissile()
{
	vecMissileList.push_back(missileFactory->AddMissile());
	vecMissileList.back()->SetOwner(owner);
}
