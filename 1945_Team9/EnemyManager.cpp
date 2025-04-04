#include "EnemyManager.h"
#include "MissileManager.h"
#include "Enemy.h"
#include "Missile.h"
#include "DiagonalEnemy.h"

//test
#include "HorizontalEnemy.h"
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
	diagonalAppearCoolTime = 10.0f;
	diagonalMaxAppearTime = 5.0f;
	diagonalMaxAppearCount = 40;
	diagonalAppearCount = 40;
	diagonalElapsedCoolTime = 0.0f;

	//
	vecEnemys[(int)EnemyType::Horizontal].resize(5);
	for (int i = 0; i < vecEnemys[(int)EnemyType::Horizontal].size(); i++)
	{
		vecEnemys[(int)EnemyType::Horizontal][i] = new HorizontalEnemy();
		vecEnemys[(int)EnemyType::Horizontal][i]->Init(-200, -200);
		vecEnemys[(int)EnemyType::Horizontal][i]->SetTarget(target);
	}
	horizontalAppearCoolTime = 13.0f;
	horizontalMaxAppearTime = 7.0f;
	horizontalMaxAppearCount = 30;
	horizontalAppearCount = 30;
	horizontalElapsedCoolTime = 0.0f;

	vecEnemys[(int)EnemyType::Straight].resize(3);
	int straigntSize = vecEnemys[(int)EnemyType::Straight].size();
	for (int i = 0; i < straigntSize; i++)
	{
		vecEnemys[(int)EnemyType::Straight][i] = new StraightEnemy();
		vecEnemys[(int)EnemyType::Straight][i]->Init(-200, -200);
		vecEnemys[(int)EnemyType::Straight][i]->SetTarget(target);
	}

	boss = new Boss;
	boss->Init(-200, -200);
	boss->SetTarget(target);
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
	if (boss)
	{
		boss->Release();
		delete boss;
		boss = nullptr;
	}
}

void EnemyManager::Update()
{
	/* -------------- 재훈 사선 enemy 코드 ---------------*/
	if (diagonalAppearCount >= diagonalMaxAppearCount)
	{
		diagonalElapsedCoolTime += TimeManager::GetInstance()->GetDeltaTime();
	}

	if (diagonalElapsedCoolTime > diagonalAppearCoolTime)
	{
		diagonalElapsedCoolTime = 0;
		diagonalAppearCount = 0;
	}

	if (diagonalAppearCount < diagonalMaxAppearCount)
		DiagonalAppear();
	/* -------------- --------------------- ---------------*/

	//test
	if (horizontalAppearCount >= horizontalMaxAppearCount)
	{
		horizontalElapsedCoolTime += TimeManager::GetInstance()->GetDeltaTime();
	}

	if (horizontalElapsedCoolTime > horizontalAppearCoolTime)
	{
		horizontalElapsedCoolTime = 0;
		horizontalAppearCount = 0;
	}

	if (horizontalAppearCount < horizontalMaxAppearCount)
		HorizontalAppear();
	

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

	StraightAppear();
		
	bossSpawnTime += TimeManager::GetInstance()->GetDeltaTime();
	if (!isBossSpawned && bossSpawnTime >= 10.0f)
	if (!isBossSpawned && bossSpawnTime >= 0.1f)
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

	if (boss)
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
	int alive = 0;
	diagonalElpasedTime += TimeManager::GetInstance()->GetDeltaTime();
	static int dy = 1;
	int diagonalSize = vecEnemys[(int)EnemyType::Diagonal].size();

	if (diagonalElpasedTime >= 7.0f)
	{
		diagonalElpasedTime = 0;
		for (int i = 0; i < diagonalSize; ++i)
		{
			if (vecEnemys[(int)EnemyType::Diagonal][i]->GetIsAlive())
				continue;

			//vecEnemys[(int)EnemyType::Diagonal][i]->ChangeApperSide();

			int appearX = vecEnemys[(int)EnemyType::Diagonal][i]->GetIsLeft() ? 20 : WINSIZE_X - 20;
			int dX = vecEnemys[(int)EnemyType::Diagonal][i]->GetIsLeft() ? -(i * 30) : i * 30;
			int dY = -5 * i + (float)dy * 30;

			vecEnemys[(int)EnemyType::Diagonal][i]->Reset({ (float)appearX + dX, float(100 + dY) });
			dy *= -1;
			diagonalAppearCount++;
		}
	}

	
	
}

void EnemyManager::HorizontalAppear()
{
	horizontalElpasedTime += TimeManager::GetInstance()->GetDeltaTime();
	int horizontalSize = vecEnemys[(int)EnemyType::Horizontal].size();

	if (horizontalElpasedTime >= 5.0f)
	{
		horizontalElpasedTime = 0;
		for (int i = 0; i < horizontalSize; ++i)
		{
			if (vecEnemys[(int)EnemyType::Horizontal][i]->GetIsAlive())
				continue;

			vecEnemys[(int)EnemyType::Horizontal][i]->ChangeApperSide();

			int appearX = vecEnemys[(int)EnemyType::Horizontal][i]->GetIsLeft() ? -50 : WINSIZE_X +50;
			int dX = vecEnemys[(int)EnemyType::Horizontal][i]->GetIsLeft() ? -(i * 50) : i * 50;
			int dY =  30-(i*20);

			vecEnemys[(int)EnemyType::Horizontal][i]->Reset({ (float)appearX + dX, float(100 + dY) });
			diagonalAppearCount++;
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
