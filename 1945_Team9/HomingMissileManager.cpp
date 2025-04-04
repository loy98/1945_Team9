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
	if (CheckIsTarget())
	{
		UpdateTargetList();
		for (int j = 0; j < vecvecMissileList[num].size(); j++)
		{
			vecvecMissileList[num][j]->ReLoad({ pos.x - (25 * vecvecMissileList[num].size() / 2) + (50 * j), pos.y + 30 });
			vecvecMissileList[num][j]->SetTarget(UpdateTarget(j));
		}
	}
	else
	{
		for (int j = 0; j < vecvecMissileList[num].size(); j++)
		{
			vecvecMissileList[num][j]->ReLoad({ pos.x - (25 * vecvecMissileList[num].size() / 2) + (50 * j), pos.y + 30 });
			vecvecMissileList[num][j]->SetAngle(DEG_TO_RAD(90.0f));
		}
	}
}

void HomingMissileManager::UpdateTargetList()
{
	//// Ÿ�� ����Ʈ ����-���� ����
	//// ���� �޾ƿ�-�浹 ���� ������� �޾ƿ´�.(������ �����ϹǷ�)
	
	bool isNewTarget = true;

	for (int i = 0; i < CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).size(); i++)
	{
		if (CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetOwner()->GetObjectType() == ObjectType::Enemy)
		{
			for (int j  = 0; j < targetList.size(); j++)
			{
				if (targetList[j] == CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetOwner())
				{
					isNewTarget = false;
					break;
				}
			}
			if (isNewTarget)
			{
				//if (CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetIsCollision())	// �浹 �ƴϸ�-��
					targetList.push_back(CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetOwner());
					// ���� push_back
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
}

GameObject * HomingMissileManager::UpdateTarget(int num)
{
	SortTargetList();

	int count = 0;

	for (int i = 0; i < targetList.size(); i++)
	{
		if (!targetList[i]->GetIsCollision()&& targetList[i]->GetIsAlive())
		{
			if (count == num)
			{
				return targetList[i];
			}
			count++;
		}
	}

	return nullptr;
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

bool HomingMissileManager::CheckIsTarget()
{
	for (int i = 0; i < CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).size(); i++)
	{
		if (CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetOwner()->GetObjectType() == ObjectType::Enemy)
		{
			if (!(CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetOwner()->GetIsCollision())
					&&CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).at(i)->GetOwner()->GetIsAlive())
				{
					return true;
				}

		}

	}
	return false;
}

void HomingMissileManager::ResetMissile(int num)
{
	vecvecMissileList[num].push_back(missileFactory->AddMissile(collisionGroup));
}

HomingMissileManager::HomingMissileManager()
{
}

HomingMissileManager::~HomingMissileManager()
{
}

void HomingMissileManager::Init()
{
	missile = 2;

	vecvecMissileList.reserve(5);
	missileFactory = new HomingMissileFactory;
	for (int i = 0; i < vecvecMissileList.capacity(); i++)
	{
		AddMissile();
	}

	targetList.reserve(CollisionManager::GetInstance()->GetColliderList(CollisionGroup::Enemy).size());
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

	targetList.clear();
}

void HomingMissileManager::Update()
{
	for(int i = 0; i< vecvecMissileList.size(); i++)
	{
		if(isActivedPack(i))
		{
			for (iter = vecvecMissileList[i].begin(); iter != vecvecMissileList[i].end(); iter++)
			{
				if((*iter)->GetIsActived())
				{
					//if (!((*iter)->GetHasTarget()) && CheckIsTarget())	// �߻��ϰ� ���� ���� Ÿ������ ����
					//{
					//	UpdateTargetList();
					//	(*iter)->SetTarget(UpdateTarget(0));
					//}
					//else
					{
						(*iter)->Update();
					}
				}
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
				if((*iter)->GetIsActived())
				{
					(*iter)->Render(hdc, isFlip);
				}
			}
		}
	}
}

void HomingMissileManager::Launch(FPOINT pos)
{
	for (int i = 0; i < vecvecMissileList.size(); i++)
	{
		if (!isActivedPack(i))
		{
			if (vecvecMissileList[i].size() < missile)
			{
				ResetMissile(i);
			}
			LaunchPack(i, pos);
			break;
		}
	}
}

void HomingMissileManager::AddMissile()
{
	vector<Missile*> pack;
	pack.resize(missile);

	for (int i = 0; i < pack.size(); i++)
	{
		pack.at(i) = missileFactory->AddMissile(collisionGroup);
	}

	vecvecMissileList.push_back(pack);
}

void HomingMissileManager::LevelUp()
{
	missile++;
}
