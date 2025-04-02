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
	void StraightAppear();

private:
	vector<Enemy*> vecEnemys[(int)EnemyType::EnemyTypeLength];
	GameObject* target;

	float diagonalElpasedTime;
	float diagonalMaxAppearTime;
	float diagonalAppearCoolTime;
	float diagonalElapsedCoolTime;
	int diagonalAppearCount;
	int diagonalMaxAppearCount;

	float straightElpasedTime;
	int straightAppearCount;
};

