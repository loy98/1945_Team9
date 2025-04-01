#pragma once
#include "GameObject.h"
class Image;
class Item : public GameObject
{
public:
	Item();
	~Item();

	void Init(FPOINT pos, FPOINT size);
	void Update();
	void Release();
	void Render(HDC hdc);

	bool GetIsDead() { return isDead; }
	
protected:
	Image* image;
	FPOINT dir;
	float moveSpeed;
	float angle;
	float lifeTime;
	float elapsedTime;
	float elapsedAnimTime;

	int animationFrame;
	int maxAnimationFrame;
	int offsetX;
	int offsetY;
	
	bool isDead;
};

