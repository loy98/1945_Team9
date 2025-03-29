#pragma once
#include "Missile.h"

class LaserMissile : public Missile
{
public:
	using Super = Missile;

	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Move() override;
	void LaserMissileMove() override;
private:
	float elapsedlaunchTime;
	float launchTime;
	bool isLaunch;
};

