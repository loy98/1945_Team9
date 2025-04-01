#include "EnemyManager.h"
#include "MissileManager.h"
#include "Enemy.h"
#include "Missile.h"
#include "EnemyFactory.h"

void EnemyManager::Init()
{
	//StraightEnemy
	/*vecEnemys.resize(3);
	for (int i = 0; i < 3; i++)
	{
		vecEnemys[i] = new Enemy();                                                                          
		vecEnemys[i]->Init(20.0f + 10.0f * (i % 3), 30.0f + 10.0f * (i / 3));
	}*/

	EnemyList.reserve(5);
	factoryList[(int)(EnemyType::Straight)] = new StraightEnemyFactory();

	//vecEnemys.resize(10);
	//for (int i = 0; i < 10; i++)
	//{
	//	vecEnemys[i] = new Enemy();
	//	vecEnemys[i]->Init(100.0f + 80.0f * (i % 5), 200.0f + 80.f * (i / 5));
	//}
	elapsedTime = 0.0f;
	rushTime = 4.0f;
}

void EnemyManager::Release()
{
	for (auto& enemy : EnemyList)
	{
		if (enemy)
		{
			enemy->Release();
			delete enemy;
			enemy = nullptr;
		}
	}

	for (auto& factory : factoryList)
	{
		if (factory)
		{
			delete factory;
			factory = nullptr;
		}
	}

	/*for (int i = 0; i < 10; i++)
	{
		if (vecEnemys[i])
		{
			vecEnemys[i]->Release();
			delete vecEnemys[i];
		}
	}
	vecEnemys.clear();*/
}

void EnemyManager::Update()
{
	for (auto& enemy : EnemyList)
	{
		if (enemy && enemy->GetIsAlive())
			enemy->Update();
	}

	/*for (int i = 0; i < vecEnemys.size(); i++)
	{
		if (vecEnemys[i])
		{
			vecEnemys[i]->Update();
			if (vecEnemys[i]->IsOutofScreen())
			{
				vecEnemys[i]->SetIsAlive(false);
			}
		}
	}*/
	elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	if (elapsedTime > rushTime)
	{
		int randNum = rand() % vecEnemys.size();
		Enemy* randEnemy = vecEnemys[randNum];
		if (randEnemy && !randEnemy->GetIsRush())
		{
			randEnemy->SetIsRush(true);
			MissileManager* m = randEnemy->GetMissileManager();

			Missile* missile = m->CreateMissile(MissileType::Normal, randEnemy->GetPos(),
				randEnemy->GetAngle(), randEnemy->GetRushSpeed() + 50);

			missile->AddCollider(CollisionGroup::Enemy);
			m->AddMissile(missile);
		}
		elapsedTime = 0.0f;
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (auto enemy : EnemyList)
	{
		if (enemy)
			enemy->Render(hdc);
	}

	//int size = vecEnemys.size();
	//for (int i = 0; i < size/*vecEnemys.size()*/; i++)
	//{
	//	if (vecEnemys[i])
	//		vecEnemys[i]->Render(hdc);
	//}
}

void EnemyManager::AddEnemy(Enemy* enemy)
{
	EnemyList.push_back(enemy);

	/*for (int i = 0; i < size; i++)
	{
		Enemy* enemy = new Enemy();
		enemy->Init(0, 0);
		vecEnemys.push_back(enemy);
	}*/
}

Enemy* EnemyManager::CreateEnemy(EnemyType type, FPOINT pos, float angle, float speed)
{
	switch (type)
	{
	case EnemyType::Straight:
		return factoryList[(int)EnemyType::Straight]->CreateEnemy(pos,angle,speed);
	}
}
