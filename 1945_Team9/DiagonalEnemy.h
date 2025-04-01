#pragma once
#include "Enemy.h"
class DiagonalEnemy : public Enemy
{
public:
	using Super = Enemy;
	DiagonalEnemy();
	~DiagonalEnemy();

	void Init(float posX, float posY) override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Reset(FPOINT pos);
	void Move() override;

protected:

};

