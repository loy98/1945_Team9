#pragma once
#include "MissileManager.h"

class MissileFactory;
class Missile;
class BossMissileManager : public MissileManager
{
private:
	vector<Missile*> vecMissileList;

public:
	BossMissileManager();
	virtual ~BossMissileManager();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;
	virtual void Launch(FPOINT pos) override;
	void AngleLaunch(FPOINT pos, float angle) override;

	virtual void AddMissile() override;
	virtual void LevelUp() override;
};

