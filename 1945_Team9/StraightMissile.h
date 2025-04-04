#pragma once
#include "Missile.h"

class Image;
class StraightMissile : public Missile
{
public:
	using Super = Missile;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;

	StraightMissile();
	~StraightMissile();

private:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
	Image* image;
	int animationFrame;
	int elapsedFrame;
	float elapsedTime;
	float elapsedMoveTime;
	float maxMoveTime;
};