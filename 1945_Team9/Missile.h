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

	virtual void Init() =0;		// �� init���� ������, isactived, moveSpeed, angle, �̹���,  addCollider
	virtual void Release();
	virtual void Update();		// active�� ��쿡��. move, isActived ����. �����̻����� ��� target pos����.-�����ſ� �߰��ϴ� ��������.
	virtual void Render(HDC hdc, bool isFlip);		// active�� ��� ����.
	
	void AddCollider(Missile* missile, CollisionGroup group);
	//void ReLoad(FPOINT pos, float angle);	
	void ReLoad(FPOINT pos);	// �߻��� ��� ����. �÷��̾��� ��ġ�� �޴´�.
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

