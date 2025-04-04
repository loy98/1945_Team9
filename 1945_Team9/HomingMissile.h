#pragma once
#include "Missile.h"
#include <vector>

class Image;
class HomingMissile: public Missile
{
private:
	Image* idle;
	Image* left;
	Image* right;
	vector<Image*>::iterator iter;

	Image* currentAnimation;

	float currAngle;
	float prevAngle;

	int currentFrame;
	int maxFrame;

	float elapsedTime;

	void UpdateImage();

	void MoveToTheRight();
	void MoveToTherLeft();

public:
	using Super = Missile;
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;

	/*
	bool isActived;
	float moveSpeed;
	float angle;
	FPOINT destination;

	GameObject* owner;
	MissileController* controller;
	*/
};

