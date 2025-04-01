#pragma once
#include "Missile.h"
#include <vector>

class Image;
class HomingMissile: public Missile
{
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;
	virtual void ReLoad(FPOINT pos) override;

	virtual void Move() override;
private:
	Image* idle;
	int animationFrame;
	vector<Image*> left;
	vector<Image*> right;
	FPOINT currPos;
	FPOINT prevPos;

	void UpdateImage();

	/*
	bool isActived;
	float moveSpeed;
	float angle;
	FPOINT destination;

	GameObject* owner;
	MissileController* controller;
	*/
};

