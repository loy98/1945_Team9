#include "StraightMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"


bool StraightMissileManager::isActivedPack(int num)
{
	for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
	{
		if ((*iter)->GetIsActived())
			return true;		// �ϳ��� active�� true ����
	}

	return false;		// �� Ȱ�����°� �ƴϸ� false ����
}

void StraightMissileManager::LaunchPack(int num, FPOINT pos)
{
	//for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
	//{
	//	(*iter)->ReLoad(pos);
	//}

	for (int i = 0; i < vecvecMissileList[num].size(); i++)
	{
		vecvecMissileList[num][i]->ReLoad({pos.x - (25 * (vecvecMissileList[num].size() / 2)) + (50 * i), pos.y});
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
			LaunchPack(i, pos);

		//if (!isActivedPack(i))
		//{
		//	for (int j = 0; j < vecvecMissileList[i].size(); j++)
		//	{
		//		if (!vecvecMissileList[i][j]->GetIsActived())
		//		{
		//			vecvecMissileList[i][j]->ReLoad({ pos.x - 25 + (50 * (j % 2)), pos.y });
		//		}
		//		else break;
		//	}
			break;
		}
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

void StraightMissileManager::LevelUp()
{
}
