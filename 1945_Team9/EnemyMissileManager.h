#pragma once
#include "MissileManager.h"

class MissileFactory;
class Missile;
class Collider;
class EnemyMissileManager : public MissileManager
{
private:
	vector<Missile*> vecMissileList;
	// vector<Missile*>::iterator iter;
	// Collider* playerTarget;

public:
	EnemyMissileManager();
	virtual ~EnemyMissileManager();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;
	virtual void Launch(FPOINT pos) override;
	virtual void AngleLaunch(FPOINT pos, float angle) override;
	//virtual void Launch(FPOINT pos, float angle) ;

	virtual void AddMissile() override;
	virtual void LevelUp() override;
};

