#pragma once
#include "Missile.h"

class Image;
class NormalMissile : public Missile
{
public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;
	virtual void ReLoad(FPOINT pos) override;

	virtual void Move() override;

private:
	Image* image;
	int animationFrame;
};

