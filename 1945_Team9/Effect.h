#pragma once
#include "config.h"
class Effect
{
public:
	Effect();
	~Effect();

	void Init(const wchar_t* filepath, FPOINT pos, Size size, int offsetX, int offsetY);
	void Update();
	void Render(HDC hdc);
	void Release();

	bool GetIsDead() { return isDead; }
private:
	int currFrame;
	float currTime;
	bool isDead;
	int offsetX;
	int offsetY;

	Size size;
	FPOINT pos;
	Image* image;
};

