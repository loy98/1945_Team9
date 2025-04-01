#include "StraightMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"

StraightMissileManager::StraightMissileManager()
{
}

StraightMissileManager::~StraightMissileManager()
{
}

void StraightMissileManager::Init()
{
	vecvecMissileList.reserve(5);
	missileFactory = new StraightMissileFactory;

	for(int i = 0; i< vecvecMissileList.capacity(); i++)
	{
		AddMissile();
	}
}

void StraightMissileManager::Release()
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

void StraightMissileManager::Update()
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
		{
			if ((*iter)->GetIsActived())
				(*iter)->Update();
		}
	}
}

void StraightMissileManager::Render(HDC hdc, bool isFlip)
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
		{
			if ((*iter)->GetIsActived())
				(*iter)->Render(hdc, isFlip);
			else break;
		}
		if (iter == vecvecMissileList[i].end()) break;
	}

}

void StraightMissileManager::Launch(FPOINT pos)
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
		{
			if (!(*iter)->GetIsActived())
			{
				(*iter)->ReLoad({ pos.x - 25 + (50*i), pos.y });
			}
			else break;
		}
		if (iter == vecvecMissileList[i].end()) break;
	}
}

void StraightMissileManager::AddMissile()
{
	vector<Missile*> pack;
	pack.resize(2);
	for (int i = 0; i < pack.size(); i++)
	{
		pack.at(i) = missileFactory->AddMissile();
		//pack.back()->SetOwner(owner);
	}

	vecvecMissileList.push_back(pack);
}
