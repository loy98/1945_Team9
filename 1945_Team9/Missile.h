#pragma once
#include "GameObject.h"
#include "config.h"

class MissileController;
class Player;
class Image;
class Missile : public GameObject
{
public:
	Missile();
	virtual ~Missile();

	virtual void Init() =0;		// 각 init에서 포지션, isactived, moveSpeed, angle, 이미지,  addCollider
	virtual void Release();
	virtual void Update();		// active일 경우에만. move, isActived 상태. 유도미사일의 경우 target pos까지.-기존거에 추가하는 방향으로.
	virtual void Render(HDC hdc, bool isFlip);		// active일 경우 렌더.
	
	void AddCollider(Missile* missile, CollisionGroup group);
	//void ReLoad(FPOINT pos, float angle);	
	void ReLoad(FPOINT pos);	// 발사할 경우 세팅. 플레이어의 위치를 받는다.
	void Move();
	bool IsOutofScreen();

	inline bool GetIsActived() { return isActived; }
	float GetMoveSpeed() { return moveSpeed; }
	float GetAddSpeed() { return addSpeed; }
	float GetAngle() { return angle; }

	inline void SetIsActived(bool isActived) { this->isActived = isActived; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline void SetAngle(float angle) { this->angle = angle; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline void SetAddSpeed(float speed) { this->addSpeed = speed; }
	
	inline void SetOwner(GameObject* owner) { this->owner = owner; }

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
	MissileController* controller;
	MissileType missileType;

	GameObject *owner;
};

