#pragma once
#include "GameObject.h"
#include "config.h"

class MissileController;
class Tank;
class Image;
class Missile : public GameObject
{
public:
	Missile();
	virtual ~Missile();

	virtual void Init();		
	virtual void Release();
	virtual void Update();		
	virtual void Render(HDC hdc, bool isFlip);

	virtual void AddCollider(CollisionGroup group);
	virtual void Move();
	virtual void LaserMissileMove() {};
	virtual void ReLoad(FPOINT pos);
	bool IsOutofScreen();

	inline bool GetIsActived() { return isActived; }
	float GetMoveSpeed() { return moveSpeed; }
	float GetAddSpeed() { return addSpeed; }
	float GetAngle() { return angle; }

	inline void SetIsActived(bool isActived) { this->isActived = isActived; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline void SetAngle(float angle) { this->angle = angle; }
	void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	void SetAddSpeed(float speed) { this->addSpeed = speed; }
	void SetOwner(GameObject* tank) { owner = tank; }


protected:
	bool isActived;
	float moveSpeed;
	float addSpeed;
	float angle;
	FPOINT destination;

	float offsetX;
	float offsetY;
	Image* image;
	int animationFrame;
	int maxAnimationFrame;
	GameObject* owner;
	MissileController* controller;
	MissileType missileType;
};

