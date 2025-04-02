#pragma once
#include "MissileManager.h"
class HomingMissileManager: public MissileManager
{
private:
	vector<vector<Missile*>> vecvecMissileList;
	vector<Missile*>::iterator iter;

	bool isActivedPack(int num);
	void LaunchPack(int num);
public:
	HomingMissileManager();
	virtual ~HomingMissileManager();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;
	virtual void Launch(FPOINT pos) override;

	virtual void AddMissile() override;
	virtual void LevelUp() override;
};

