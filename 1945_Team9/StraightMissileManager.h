#pragma once
#include "MissileManager.h"

class Missile;
class StraightMissileManager: public MissileManager
{
private:
	vector<vector<Missile*>> vecvecMissileList;

	bool isActivedPack(int num);
	void LaunchPack(int num);
public:
	StraightMissileManager();
	virtual ~StraightMissileManager();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;
	virtual void Launch(FPOINT pos) override;

	virtual void AddMissile() override;
};

