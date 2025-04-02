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
	if (!isActivedPack(num))		// Ȱ�������ΰ� ������ �߻�
	{
		for (iter = vecvecMissileList[num].begin(); iter != vecvecMissileList[num].end(); iter++)
		{
			(*iter)->ReLoad(pos);
		}
	}
}

void HomingMissileManager::UpdateTarget(FPOINT pos)		// �÷��̾� ������
{
	//for (int i = 0; i < targetList.size(); i++)
	//{
	//	if (targetList.at(i) == ObjectType::Enemy)
	//	{

	//	}
	//}
	int distance = WINSIZE_Y;
	// ��Ȱ�� Ÿ�� ����
	for (targetIter = targetList.begin(); targetIter != targetList.end(); targetIter++)
	{

	}

	// Ÿ�ٺ��Ͱ� �� �� á���� �ֱ� �ƴϸ� �ֱ�

	for (targetIter = targetList.begin(); targetIter != targetList.end(); targetIter++)
	{
		if ((*targetIter)->GetOwner()->GetObjectType() == ObjectType::Enemy)	// �̻����� �ƴ϶� ���̶��
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
	// ���� �浹 ��ġ �޾ƿ���, �� �� �ϳ��� Ÿ������ �Ѵ�. ���� Ÿ���� ������ Ÿ�� ����, �ε������� ��

	// Ÿ�� ����Ʈ ����
	for (targetIter = targetList.begin(); targetIter != targetList.end(); targetIter++)
	{
		if ((*targetIter)->GetOwner()->GetObjectType() != ObjectType::Enemy)	// ���� �ƴ϶��
		{
			targetList.erase(targetIter);	// ����
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
