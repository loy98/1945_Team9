#pragma once
#include "Missile.h"

class Image;
class EnemyMissile : public Missile
{
public : 
	using Super = Missile;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;

	void SetOwner(GameObject* owner) { this->owner = owner; };

	EnemyMissile();
	~EnemyMissile();

private:
	Image* image;
	int animationFrame;
	int elapsedFrame;
	float elapsedTime;
	float elapsedMoveTime;
	float maxMoveTime;
	GameObject* owner;
};

