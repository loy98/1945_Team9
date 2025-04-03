#pragma once
#include "Enemy.h"

class HorizontalEnemy: public Enemy
{
public:
	using Super = Enemy;
	HorizontalEnemy();
	~HorizontalEnemy();

	void Init(float posX, float posY) override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Reset(FPOINT pos);
	void Move() override;
	void Fire() override;

	int GetFrameNum() { return animationFrame; }
	int GetMaxFrame();

protected:
	float elapsedFireTime;
	float maxFireTime;
};

