#pragma once
#include "GameObject.h"

class Enemy;
class EnemyManager : public GameObject
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(int size);


private:
	vector<Enemy*> vecEnemys;
	vector<Enemy*> EnemyList;

	float elapsedTime;
	float rushTime;
};

