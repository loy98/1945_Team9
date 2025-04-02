#include "EnemyManager.h"
#include "MissileManager.h"
#include "Enemy.h"
#include "Missile.h"
#include "DiagonalEnemy.h"
#include "StraightEnemy.h"
#include "Boss.h"

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
		vecEnemys[(int)EnemyType::Diagonal][i]->Init(-200, -200);
		vecEnemys[(int)EnemyType::Diagonal][i]->SetTarget(target);
	}

	vecEnemys[(int)EnemyType::Straight].resize(3);
	int straigntSize = vecEnemys[(int)EnemyType::Straight].size();
	for (int i = 0; i < straigntSize; i++)
	{
		vecEnemys[(int)EnemyType::Straight][i] = new StraightEnemy();
		vecEnemys[(int)EnemyType::Straight][i]->Init(20, -20);
		vecEnemys[(int)EnemyType::Straight][i]->SetTarget(target);
	}

	boss = new Boss;
	boss->Init(0, 0);
	boss->SetTarget(target);

	diagonalAppearCoolTime = 0.0f;
	diagonalMaxAppearTime = 0.2f;
	diagonalMaxAppearCount = 40;
	diagonalAppearCount = 40;
	diagonalElapsedCoolTime = 20.0f;
	
	bossSpawnTime = 0.0f;
	isBossSpawned = false;

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
	if(boss)
		boss->Release();
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
	if (boss)
	{
		boss->Update();

		if (boss->IsOutofScreen())
		{
			boss->SetIsAlive(false);
		}
		
	}

	if (diagonalAppearCount == diagonalMaxAppearCount)
	{
		diagonalAppearCoolTime += TimeManager::GetInstance()->GetDeltaTime();
	}
	
	if (diagonalAppearCoolTime > diagonalElapsedCoolTime)
	{
		diagonalAppearCoolTime = 0;
		diagonalAppearCount = 0;
	}

	if (diagonalAppearCount < diagonalMaxAppearCount)
	{
		DiagonalAppear();
	}

	StraightAppear();
		
	bossSpawnTime += TimeManager::GetInstance()->GetDeltaTime();

	if (!isBossSpawned && bossSpawnTime >= 10.0f)
	{
		isBossSpawned = true;
		BossAppear();
	}
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

	if (boss && boss->GetIsAlive())
	{
		boss->Render(hdc);
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
			diagonalAppearCount++;
			break;
		}
	}
}

void EnemyManager::StraightAppear()
{
	static int num = 0;
	static FPOINT pos = { 0,0};
	if (num == 0)
	{
		pos = { (float)(rand() % (WINSIZE_X - 100))  , -20.f };
	}

	int straightSize = vecEnemys[(int)EnemyType::Straight].size();
	for (int i = 0; i < straightSize; i++)
	{
		if (!vecEnemys[(int)EnemyType::Straight][i]->GetIsAlive())
		{
			float posX = pos.x;
			float posY = pos.y;
			if (num == 0)
			{
				posY += 50.0f;
			}
			else if (num == 1)
			{
				posX -= 50.0f;
			}
			else if (num == 2)
			{
				posX += 50.0f;
			}

			vecEnemys[(int)EnemyType::Straight][i]->Reset({ posX,posY});
			num = (num+1) % straightSize;
		} 
		
	}
}

void EnemyManager::BossAppear()
{
	if (!boss->GetIsAlive())
	{
		boss->Reset({ WINSIZE_X/2 ,-10 });
	}
}
