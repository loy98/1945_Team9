#pragma once
#include "Enemy.h"


class Image;
class StraightEnemy : public Enemy
{
public:
	using Super = Enemy;
	StraightEnemy();
	~StraightEnemy();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void ReLoad(FPOINT pos) override;
	virtual void Move() override;

private:
	Image* image;
};

