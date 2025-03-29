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
	vector<Enemy*> vecEnemys/*{10, new Enemy()}*/;

	float elapsedTime;
	float rushTime;
};

