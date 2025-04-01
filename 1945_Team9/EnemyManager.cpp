#include "EnemyManager.h"
#include "MissileManager.h"
#include "Enemy.h"
#include "Missile.h"
#include "DiagonalEnemy.h"

EnemyManager::EnemyManager(GameObject* target) : target(target)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	vecEnemys[(int)EnemyType::Diagonal].resize(10);
	int diagonalSize = vecEnemys[(int)EnemyType::Diagonal].size();
	for (int i = 0; i < diagonalSize; i++)
	{
		vecEnemys[(int)EnemyType::Diagonal][i] = new DiagonalEnemy();
		vecEnemys[(int)EnemyType::Diagonal][i]->Init(-20, -20);
		vecEnemys[(int)EnemyType::Diagonal][i]->SetTarget(target);
	}
	elapsedTime = 0.0f;
	diagonalMaxAppearTime = 0.2f;
	diagonalMaxAppearCount = 4;
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
	//if (diagonalAppearCount == diagonalMaxAppearCount) return;

	diagonalElpasedTime += TimeManager::GetInstance()->GetDeltaTime();
	static int dy = 1;
	
	int diagonalSize = vecEnemys[(int)EnemyType::Diagonal].size();
	if (diagonalElpasedTime >= diagonalMaxAppearTime)
	{
		for (int i = 0; i < diagonalSize; ++i)
		{
			diagonalElpasedTime = 0;
			if (vecEnemys[(int)EnemyType::Diagonal][i]->GetIsAlive())
				continue;
			vecEnemys[(int)EnemyType::Diagonal][i]->ChangeApperSide();

			int appearX = vecEnemys[(int)EnemyType::Diagonal][i]->GetIsLeft() ? 20 : WINSIZE_X - 20;
			vecEnemys[(int)EnemyType::Diagonal][i]->Reset({ (float)appearX, 100 + (float)dy * 30 });
			dy *= -1;
			break;
		}
	}
	//diagonalAppearCount++;
	//DiagonalAppear(left);
}
