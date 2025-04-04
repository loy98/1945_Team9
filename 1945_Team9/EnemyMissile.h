#pragma once
#include "Missile.h"

class EnemyMissile : public Missile
{
public : 

	using Super = Missile;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;
};

