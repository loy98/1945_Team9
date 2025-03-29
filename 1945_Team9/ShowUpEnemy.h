#pragma once
#include "Enemy.h"
class ShowUpEnemy : public Enemy
{
public:
	using Super = Enemy;
	ShowUpEnemy();
	~ShowUpEnemy();

	virtual void Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Move();

};

