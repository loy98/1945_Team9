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
			return true;		// �ϳ��� active�� true ����
	}

	return false;		// �� Ȱ�����°� �ƴϸ� false ����
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

	//// ���� �浹 ��ġ �޾ƿ���, �� �� �ϳ��� Ÿ������ �Ѵ�. ���� Ÿ���� ������ Ÿ�� ����, �ε������� ��

	//// Ÿ�� ����Ʈ ����-���� ����



	//// ���� �浹 ��ġ �޾ƿ���, �� �� �ϳ��� Ÿ������ �Ѵ�. ���� Ÿ���� ������ Ÿ�� ����, �ε������� ��

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
				if (!CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetIsCollision())	// �浹 �ƴϸ�
					targetList.push_back(CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i));	// �� collision�� push_back
			}

		}

	}

	// ��Ȱ�� Ÿ�� ����-�����ϴϱ� �� �ɸ��µ�

	//for (int i = 0; i < targetList.size(); i++)
	//{
	//	if (targetList.at(i)->GetIsCollision())
	//	{
	//		targetList.erase(targetList.begin()+i);
	//	}
	//}

	//for (targetIter = targetList.begin(); targetIter != targetList.end(); targetIter++)		// ����Ʈ�� 10�������� �ݺ������� ��.
	//{
	//	if ((*targetIter)->GetIsCollision())	// �浹�� ���¸� ����
	//	{
	//		targetList.erase(targetIter);
	//	}
	//}

	SortTargetList();
}

void HomingMissileManager::SortTargetList()
{
	float maxIndex;	// y���� ũ�� �� ����

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
