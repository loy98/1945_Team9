#include "EnemyManager.h"
#include "MissileManager.h"
#include "Enemy.h"
#include "Missile.h"

void EnemyManager::Init()
{
	vecEnemys.resize(10);
	for (int i = 0; i < 10; i++)
	{
		vecEnemys[i] = new Enemy();
		vecEnemys[i]->Init(100.0f + 80.0f * (i % 5), 200.0f + 80.f * (i / 5));
	}
	elapsedTime = 0.0f;
	rushTime = 4.0f;
}

void EnemyManager::Release()
{
	for (int i = 0; i < 10; i++)
	{
		if (vecEnemys[i])
		{
			vecEnemys[i]->Release();
			delete vecEnemys[i];
		}
	}
	vecEnemys.clear();
}

void EnemyManager::Update()
{
	for (int i = 0; i < vecEnemys.size(); i++)
	{
		if (vecEnemys[i])
		{
			vecEnemys[i]->Update();
			if (vecEnemys[i]->IsOutofScreen())
			{
				vecEnemys[i]->SetIsAlive(false);
			}
		}
	}
	//elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	//if (elapsedTime > rushTime)
	//{
	//	int randNum = rand() % vecEnemys.size();
	//	Enemy* randEnemy = vecEnemys[randNum];
	//	if (randEnemy && !randEnemy->GetIsRush())
	//	{
	//		randEnemy->SetIsRush(true);
	//		MissileManager* m = randEnemy->GetMissileManager();

	//		Missile* missile = m->CreateMissile(MissileType::Normal, randEnemy->GetPos(),
	//			randEnemy->GetAngle(), randEnemy->GetRushSpeed() + 50);

	//		missile->AddCollider(CollisionGroup::Enemy);
	//		m->AddMissile(missile);
	//	}
	//	elapsedTime = 0.0f;
	//}
}

void EnemyManager::Render(HDC hdc)
{
	int size = vecEnemys.size();
	for (int i = 0; i < size/*vecEnemys.size()*/; i++)
	{
		if (vecEnemys[i])
			vecEnemys[i]->Render(hdc);
	}
}

void EnemyManager::AddEnemy(int size)
{
	for (int i = 0; i < size; i++)
	{
		Enemy* enemy = new Enemy();
		enemy->Init(0, 0);
		vecEnemys.push_back(enemy);
	}
}
