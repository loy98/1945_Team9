#pragma once
#include "Enemy.h"

class Image;
class StraightEnemy : public Enemy
{
public:
	using Super = Enemy;
	StraightEnemy();
	~StraightEnemy();

	void Init(float posX, float posY) override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	
	void Reset(FPOINT pos);
	void Move() override;
	void Fire() override;

private:
	float fireTime;
	float maxFireTime;
};