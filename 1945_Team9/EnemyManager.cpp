#include "EnemyManager.h"
#include "MissileManager.h"
#include "Enemy.h"
#include "Missile.h"
#include "DiagonalEnemy.h"

void EnemyManager::Init()
{
	vecEnemys[(int)EnemyType::Diagonal].resize(10);
	int diagonalSize = vecEnemys[(int)EnemyType::Diagonal].size();
	for (int i = 0; i < diagonalSize; i++)
	{
		vecEnemys[(int)EnemyType::Diagonal][i] = new DiagonalEnemy();
		vecEnemys[(int)EnemyType::Diagonal][i]->Init(-20, -20);
	}
	elapsedTime = 0.0f;
	diagoanlMaxAppearTime = 0.2f;
}

void EnemyManager::Release()
{
	for (int i = 0; i < (int)EnemyType::EnemyTypeLength; ++i)
	{
		for (int j = 0; j < vecEnemys[i].size(); ++j)
		if (vecEnemys[i][j])
		{
			vecEnemys[i][j]->Release();
			delete vecEnemys[i][j];
		}
		vecEnemys[i].clear();
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < (int)EnemyType::EnemyTypeLength; ++i)
	{
		for (int j = 0; j < vecEnemys[i].size(); ++j)
		{
			if (vecEnemys[i][j])
			{
				vecEnemys[i][j]->Update();
				if (vecEnemys[i][j]->IsOutofScreen())
				{
					vecEnemys[i][j]->SetIsAlive(false);
				}
			}
		}
	}
	DiagonalAppear();
}

void EnemyManager::Render(HDC hdc)
{
	for (int i = 0; i < (int)EnemyType::EnemyTypeLength; ++i)
	{
		for (int j = 0; j < vecEnemys[i].size(); ++j)
		{
			if (vecEnemys[i][j])
			{
				vecEnemys[i][j]->Render(hdc);
			}
		}
	}

}

void EnemyManager::AddEnemy(int size)
{
	for (int i = 0; i < size; i++)
	{
		Enemy* enemy = new Enemy();
		enemy->Init(0, 0);
		//vecEnemys.push_back(enemy);
	}
}

void EnemyManager::DiagonalAppear()
{
	diagoanlElpasedTime += TimeManager::GetInstance()->GetDeltaTime();
	static int num = 1;
	int diagonalSize = vecEnemys[(int)EnemyType::Diagonal].size();
	if (diagoanlElpasedTime >= diagoanlMaxAppearTime)
	{
		for (int i = 0; i < diagonalSize; ++i)
		{
			diagoanlElpasedTime = 0;
			if (vecEnemys[(int)EnemyType::Diagonal][i]->GetIsAlive())
				continue;
			vecEnemys[(int)EnemyType::Diagonal][i]->Reset({ 0, 100 + (float)num * 30 });
			num *= -1;
			break;
		}

	}

}
