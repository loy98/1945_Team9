#pragma once
#include "Missile.h"
class NormalMissile : public Missile
{
public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void ReLoad(FPOINT pos) override;

	virtual void Move() override;
};

