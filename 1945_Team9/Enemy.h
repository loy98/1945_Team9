#pragma once
#include "GameObject.h"

class Tank;
class Image;
class MissileManager;
class Enemy : public GameObject	// is-a
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init(float posX, float posY);		
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);

	virtual void Move();
	virtual void Reset(FPOINT pos);
	void Rush();
	bool IsOutofScreen();

	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return isAlive; }
	void SetIsRush(bool isRush) { this->isRush = isRush; }
	bool GetIsRush() { return isRush; }

	inline void SetTarget(Tank* target) { this->target = target; }
	inline FPOINT GetPos() { return pos; }
	float GetAngle() { return angle; }
	float GetMoveSpeed() { return moveSpeed; }
	float GetRushSpeed() { return rushSpeed; }
	MissileManager* GetMissileManager() { return missileManager; }

protected:
	FPOINT dir{ 1, 0 };
	float moveSpeed;
	float rushSpeed;
	float angle;
	bool isAlive;
	int animationFrame;
	int elapsedFrame;
	float elapsedTime;
	float elapsedMoveTime;
	float maxMoveTime;
	Tank* target;
	bool isRush;

	Image* image;
	MissileManager* missileManager;
};

