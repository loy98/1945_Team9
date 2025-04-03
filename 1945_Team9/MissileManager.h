#pragma once
#include "GameObject.h"
#include "config.h"
class Missile;
class MissileFactory;
class MisisileController;
class MissileManager : public GameObject
{
public:
	MissileManager();
	virtual ~MissileManager();

	virtual void Init() = 0;
	virtual void Release() = 0;

	virtual void Update() = 0;
	virtual void Render(HDC hdc, bool isFlip) = 0;
	virtual void Launch(FPOINT pos) = 0;
	virtual void AngleLaunch(FPOINT pos, float angle);

	virtual void AddMissile() = 0;		// 팩토리에서 addMissile 불러옴.
	//const int GetMissileListSize() { return vecMissileList.size(); }

	inline void SetOwner(GameObject * owner){ this->owner = owner; }
	inline void SetCollisionGroup(CollisionGroup group) { this->collisionGroup = group; }

	virtual void LevelUp() = 0;
protected:
	MissileFactory* missileFactory;
	vector<Missile*>::iterator iter;
	GameObject* owner;
	CollisionGroup collisionGroup;

	//FPOINT pos;		// 미사일에게 넘겨줄 포지션(플레이어 포지션)
	//float angle;	// 미사일에게 넘겨줄 각도
};



