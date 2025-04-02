#pragma once
#include "GameObject.h"

class Player;
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
	virtual void Fire();
	virtual void Reset(FPOINT pos);
	void ChangeApperSide();
	bool IsOutofScreen();

	bool GetIsLeft() { return isLeft; }


	//inline void SetTarget(Player* target) { this->target = target; }
	inline void SetTarget(GameObject* target) { this->target = target; }

	inline FPOINT GetPos() { return pos; }
	float GetAngle() { return angle; }
	float GetMoveSpeed() { return moveSpeed; }
	MissileManager* GetMissileManager() { return missileManager; }

protected:
	FPOINT dir{ 1, 0 };
	float moveSpeed;
	float angle;
	
	int animationFrame;
	int elapsedFrame;
	float elapsedTime;
	float elapsedMoveTime;
	float maxMoveTime;
	float elapsedApperTime;

	//Player* target;
	GameObject* target;
	bool isLeft;
	bool isEffect;

	float offsetX;
	float offsetY;

	Image* image;
	MissileManager* missileManager;
};

