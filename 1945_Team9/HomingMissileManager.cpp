#include "HomingMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"

bool HomingMissileManager::isActivedPack(int num)
{
	for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
	{
		if ((*iter)->GetIsActived())
			return true;		// �ϳ��� active�� true ����
	}

	return false;		// �� Ȱ�����°� �ƴϸ� false ����
}

void HomingMissileManager::LaunchPack(int num)
{
	if (!isActivedPack(num))		// Ȱ�������ΰ� ������ �߻�
	{
		for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
		{
			(*iter)->ReLoad(pos);
		}
	}
}

HomingMissileManager::HomingMissileManager()
{
}

HomingMissileManager::~HomingMissileManager()
{
}

void HomingMissileManager::Init()
{
	vecvecMissileList.reserve(5);
	missileFactory = new HomingMissileFactory;
	for (int i = 0; i < vecvecMissileList.capacity(); i++)
	{
		AddMissile();
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
		if(isActivedPack(i))
		{
			for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
			{
				(*iter)->Update();
			}
		}
	}
}

void HomingMissileManager::Render(HDC hdc, bool isFlip)
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		if(isActivedPack(i))
		{
			for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
			{
				(*iter)->Render(hdc, isFlip);
			}
		}
	}
}

void HomingMissileManager::Launch(FPOINT pos)
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		LaunchPack(i); 
	}
}

void HomingMissileManager::AddMissile()
{
	vector<Missile*> pack;
	pack.resize(2);

	for (int i = 0; i < pack.size(); i++)
	{
		pack.at(i) = missileFactory->AddMissile(collisionGroup);
		//pack.back()->SetOwner(owner);
	}

	vecvecMissileList.push_back(pack);
}
