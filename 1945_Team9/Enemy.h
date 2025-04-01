#pragma once
#include "GameObject.h"

class Tank;
class Image;
class EnemyManager;
class EnemyController;
class MissileManager;
class Enemy : public GameObject	// is-a
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init();		
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);
	virtual void ReLoad(FPOINT pos);

	virtual void Move();
	void showEnemy(EnemyType type);
	void AddEnemy(EnemyType type, FPOINT pos, float angle, float speed);
	void Rush();
	bool IsOutofScreen();

	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return isAlive; }
	void SetIsRush(bool isRush) { this->isRush = isRush; }
	bool GetIsRush() { return isRush; }

	inline void SetTarget(Tank* target) { this->target = target; }
	inline FPOINT GetPos() { return pos; }
	inline FPOINT SetPos(FPOINT pos) { this->pos = pos; }
	float GetAngle() { return angle; }
	float SetAngle(float angle) { this->angle = angle; }
	float GetMoveSpeed() { return moveSpeed; }
	float SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	float GetRushSpeed() { return rushSpeed; }
	MissileManager* GetMissileManager() { return missileManager; }

protected:
	FPOINT pos;
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
	EnemyManager* enemyManager;
	EnemyController* controller;
	MissileManager* missileManager;
};

