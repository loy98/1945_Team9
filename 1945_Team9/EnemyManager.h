#pragma once
#include "GameObject.h"

class Enemy;
class EnemyFactory;
class EnemyManager : public GameObject
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(Enemy* enemy);
	Enemy* CreateEnemy(EnemyType type, FPOINT pos, float angle, float speed);

private:
	vector<Enemy*> vecEnemys;
	vector<Enemy*> EnemyList;
	vector<EnemyFactory*> factoryList{ (int)(EnemyType::EnemyTypeLength), nullptr };

	float elapsedTime;
	float rushTime;
};

