#include "HomingMissileManager.h"
#include "MissileFactory.h"
#include "Missile.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "CommonFunction.h"

bool HomingMissileManager::isActivedPack(int num)
{
	for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
	{
		if ((*iter)->GetIsActived())
			return true;		// 하나라도 active면 true 리턴
	}

	return false;		// 다 활성상태가 아니면 false 리턴
}

void HomingMissileManager::LaunchPack(int num, FPOINT pos)
{
		//for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
		//{
		//	(*iter)->SetTarget(targetList[0]->GetOwner());
		//	(*iter)->ReLoad(pos);
		//}
		for (int i = 0; i < vecvecMissileList[num].size(); i++)
		{
			vecvecMissileList[num][i]->SetTarget(targetList[i]->GetOwner());
			vecvecMissileList[num][i]->ReLoad({pos.x-(25* vecvecMissileList[num].size()/2)+(50*i), pos.y+30});
		}
}

void HomingMissileManager::UpdateTarget()
{

	//// 적의 충돌 위치 받아오고, 그 중 하나를 타겟으로 한다. 만약 타겟이 죽으면 타겟 갱신, 부딪혔으면 끝

	//// 타겟 리스트 정리-적만 남게



	//// 적의 충돌 위치 받아오고, 그 중 하나를 타겟으로 한다. 만약 타겟이 죽으면 타겟 갱신, 부딪혔으면 끝

	bool isNewTarget = true;

	for (int i = 0; i < CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).size(); i++)
	{
		if (CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetOwner()->GetObjectType() == ObjectType::Enemy)
		{
			for (int j  = 0; j < targetList.size(); j++)
			{
				if (targetList[j] == CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i))
				{
					isNewTarget = false;
					break;
				}
			}
			if (isNewTarget)
			{
				if (!CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetIsCollision())	// 충돌 아니면
					targetList.push_back(CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i));	// 적 collision만 push_back
			}

		}

	}

	// 비활성 타겟 정리-정리하니까 렉 걸리는듯

	//for (int i = 0; i < targetList.size(); i++)
	//{
	//	if (targetList.at(i)->GetIsCollision())
	//	{
	//		targetList.erase(targetList.begin()+i);
	//	}
	//}

	//for (targetIter = targetList.begin(); targetIter != targetList.end(); targetIter++)		// 리스트에 10개단위로 반복적으로 들어감.
	//{
	//	if ((*targetIter)->GetIsCollision())	// 충돌한 상태면 제거
	//	{
	//		targetList.erase(targetIter);
	//	}
	//}

	SortTargetList();
}

void HomingMissileManager::SortTargetList()
{
	float maxIndex;	// y값이 크면 더 밑쪽

	for(int i = 0; i< targetList.size()-1;i++)
	{
		maxIndex = i;
		for (int j = i+1; j < targetList.size();j++)
		{
			if (targetList[j]->GetPos().y > targetList[maxIndex]->GetPos().y)
			{
				swap(targetList[j], targetList[maxIndex]);
			}
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


	float a = 4;
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

	//for (targetIter = targetList.begin(); targetIter != targetList.end(); iter++)
	//{
	//	(*targetIter)->Release();
	//	delete (*targetIter);
	//	(*targetIter) = nullptr;
	//}
	targetList.clear();


}

void HomingMissileManager::Update()
{
	UpdateTarget();

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
	//for (int i = 0; i < vecvecMissileList.size(); i++)
	//{
	//	if(isActivedPack(i))
	//	{
	//		LaunchPack(i, pos);
	//		break;
	//	}
	//}
	UpdateTarget();
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		if (!isActivedPack(i))
		{
			//LaunchPack(i);
			for (int j = 0; j < vecvecMissileList[i].size(); j++)
			{
				vecvecMissileList[i][j]->SetTarget(targetList[j]->GetOwner());
				vecvecMissileList[i][j]->ReLoad({ pos.x - (25 * vecvecMissileList[i].size() / 2) + (25 * j), pos.y + 30 });
			}
			break;
		}
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

void HomingMissileManager::LevelUp()
{
}
