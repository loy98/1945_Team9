#pragma once
#include "GameObject.h"

class MissileController;
class Tank;
class Missile : public GameObject
{
public:
	Missile();
	virtual ~Missile();

	virtual void Init();		
	virtual void Release();
	virtual void Update();		
	virtual void Render(HDC hdc, bool isFlip);

	virtual void Move();
	virtual void LaserMissileMove() {};
	virtual void ReLoad(FPOINT pos);
	bool IsOutofScreen();

	inline bool GetIsActived() { return isActived; }
	inline FPOINT GetPos() { return pos; }
	inline int GetSize() { return size; }
	float GetMoveSpeed() { return moveSpeed; }
	float GetAngle() { return angle; }

	inline void SetIsActived(bool isActived) { this->isActived = isActived; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline void SetAngle(float angle) { this->angle = angle; }
	void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	void SetOwner(Tank* tank) { owner = tank; }


protected:
	FPOINT pos;
	bool isActived;
	COLORREF color;
	float moveSpeed;
	float angle;
	FPOINT destination;
	int size;

	Tank* owner;
	MissileController* controller;
};

