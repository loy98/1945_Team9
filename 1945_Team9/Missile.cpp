#include "Missile.h"
#include "CommonFunction.h"

void Missile::Init()
{

}

void Missile::Release()
{
}

void Missile::Update()
{
	
}

void Missile::Render(HDC hdc, bool isFlip)
{
	
}

void Missile::Move()
{
	
}

void Missile::ReLoad(FPOINT pos)
{
}

bool Missile::IsOutofScreen()
{
	float right = pos.x + size / 2;
	float left = pos.x - size / 2;
	float top = pos.y - size / 2;
	float bottom = pos.y + size / 2;

	if (right < 0 || left > WINSIZE_X 
		|| bottom < 0 || top > WINSIZE_Y)
		return true;

	return false;
}

Missile::Missile()
{
}

Missile::~Missile()
{
}
