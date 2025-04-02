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
	if (!isActivedPack(num))		// 활성상태인게 없으면 발사
	{
		for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
		{
			(*iter)->ReLoad(pos);
		}
	}
}

void HomingMissileManager::UpdateTarget(FPOINT pos)		// 플레이어 포지션
{
	//for (int i = 0; i < targetList.size(); i++)
	//{
	//	if (targetList.at(i) == ObjectType::Enemy)
	//	{

	//	}
	//}
	int distance = WINSIZE_Y;
	// 비활성 타겟 정리
	for (targetIter = targetList.begin(); targetIter != targetList.end(); targetIter++)
	{

	}

	// 타겟벡터가 꽉 안 찼으면 넣기 아니면 넣기

	for (targetIter = targetList.begin(); targetIter != targetList.end(); targetIter++)
	{
		if ((*targetIter)->GetOwner()->GetObjectType() == ObjectType::Enemy)	// 미사일이 아니라 적이라면
		{
			if (targets.size() < targets.capacity())
			{
				targets.push_back((*targetIter)->GetOwner());
			}
			if (distance >= GetDistance(pos, (*targetIter)->GetPos()))
			{
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

	targetList = CollisionManager::GetInstance()->GetCollider(CollisionGroup::Enemy);
	// 적의 충돌 위치 받아오고, 그 중 하나를 타겟으로 한다. 만약 타겟이 죽으면 타겟 갱신, 부딪혔으면 끝

	// 타겟 리스트 정리
	for (targetIter = targetList.begin(); targetIter != targetList.end(); targetIter++)
	{
		if ((*targetIter)->GetOwner()->GetObjectType() != ObjectType::Enemy)	// 적이 아니라면
		{
			targetList.erase(targetIter);	// 삭제
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
		LaunchPack(i, pos); 
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
