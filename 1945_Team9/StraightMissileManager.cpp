#include "StraightMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"


bool StraightMissileManager::isActivedPack(int num)
{
	for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
	{
		if ((*iter)->GetIsActived())
			return true;		// 하나라도 active면 true 리턴
	}

	return false;		// 다 활성상태가 아니면 false 리턴
}

void StraightMissileManager::LaunchPack(int num)
{
	for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
	{
		(*iter)->ReLoad(pos);
	}
}


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
		if(isActivedPack(i))
		{
			for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
			{
				(*iter)->Update();
			}
		}
	}
}

void StraightMissileManager::Render(HDC hdc, bool isFlip)
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		if(isActivedPack(i))
		{
			vecvecMissileList[i].at(0)->Render(hdc, isFlip);
			vecvecMissileList[i].at(1)->Render(hdc, isFlip);
			//for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
			//{
			//	(*iter)->Render(hdc, isFlip);
			//}
		}
		//if (iter == vecvecMissileList[i].end()) break;
	}

}

void StraightMissileManager::Launch(FPOINT pos)
{
	int position = 0;

	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		if(!isActivedPack(i))
		{
			//LaunchPack(i);
			for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
			{
				if (!(*iter)->GetIsActived())
				{
					(*iter)->ReLoad({ pos.x - 25+position, pos.y });
					position += 50;
				}
				else break;


			}
			break;
		}
		//if (iter == vecvecMissileList[i].end()) break;
	}
}

void StraightMissileManager::AddMissile()
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
