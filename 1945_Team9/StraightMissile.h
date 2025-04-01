#pragma once
#include "Missile.h"

class Image;
class StraightMissile : public Missile
{
public:
	using Super = Missile;
	StraightMissile();
	~StraightMissile();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc, bool isFlip) override;
	virtual void ReLoad(FPOINT pos) override;

	virtual void Move() override;

private:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
	Image* image;
	int animationFrame;
	int elapsedFrame;
	float elapsedTime;
	float elapsedMoveTime;
	float maxMoveTime;
};