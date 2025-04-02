#pragma once
#include "GameObject.h"
class Image;
class Item : public GameObject
{
public:
	Item();
	virtual ~Item();

	virtual void Init(FPOINT pos, FPOINT size);
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);

	bool GetIsDead() { return isDead; }
	ItemType GetItemType() { return itemType; }
protected:
	Image* image;
	FPOINT dir;
	ItemType itemType;
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

