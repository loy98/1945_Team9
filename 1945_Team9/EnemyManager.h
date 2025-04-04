#pragma once
#include "GameObject.h"

class Enemy;
class EnemyManager : public GameObject
{
public:
	EnemyManager(GameObject* target);
	virtual ~EnemyManager();
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(int size);

	void DiagonalAppear();
	void HorizontalAppear();
	void StraightAppear();
	void BossAppear();

private:
	vector<Enemy*> vecEnemys[(int)EnemyType::EnemyTypeLength];
	Enemy* boss;
	GameObject* target;

	float diagonalElpasedTime;
	float diagonalMaxAppearTime;
	float diagonalAppearCoolTime;
	float diagonalElapsedCoolTime;
	int diagonalAppearCount;
	int diagonalMaxAppearCount;

	//
	float horizontalElpasedTime;
	float horizontalMaxAppearTime;
	float horizontalAppearCoolTime;
	float horizontalElapsedCoolTime;
	int horizontalAppearCount;
	int horizontalMaxAppearCount;

	float bossSpawnTime;
	bool isBossSpawned;


};

