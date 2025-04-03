#pragma once
#include "Missile.h"

class LaserMissile : public Missile
{
public:
	using Super = Missile;

	LaserMissile();
	virtual ~LaserMissile();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;

	void LevelUp();

	void SetOwner(GameObject* owner) { this->owner = owner; };

private:
	float elapsedlaunchTime;
	float launchTime;
	float coolTime;
	bool isLaunch;
	GameObject* owner;
};

