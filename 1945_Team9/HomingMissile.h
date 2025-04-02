#pragma once
#include "Missile.h"
#include <vector>

class Image;
class HomingMissile: public Missile
{
private:
	Image* idle;
	vector<Image*> left;
	vector<Image*> right;
	Image* currentAnimation;

	FPOINT currPos;
	FPOINT prevPos;

	int currentFrame;
	int maxFrame;

	void UpdateImage();


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

