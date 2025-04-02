#pragma once
#include "MissileManager.h"

class LaserMissileManager: public MissileManager
{
private:
	vector<Missile*> vecMissileList;
	float elapsedlaunchTime;
	float launchTime;
	bool isLaunch;

public:
	LaserMissileManager();
	virtual ~LaserMissileManager();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;
	virtual void Launch(FPOINT pos) override;
	void LevelUp() override;

	virtual void AddMissile() override;
};

