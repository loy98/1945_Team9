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

	void DiagonalAppear();
private:
	vector<Enemy*> vecEnemys[(int)EnemyType::EnemyTypeLength];

	float elapsedTime;
	float diagoanlElpasedTime;
	float diagoanlMaxAppearTime;
};

