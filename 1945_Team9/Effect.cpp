#include "Effect.h"
#include "TimeManager.h"
#include "ImageManager.h"
#include "Image.h"
Effect::Effect()
{
}

Effect::~Effect()
{
}

void Effect::Init(const wchar_t* filepath, FPOINT pos, Size size, int offsetX, int offsetY)
{
	image = ImageManager::GetInstance()->AddImage(L"EnemyDie", L"Image\\EnemyDie.bmp", 975, 64, 15, 1, false, true, RGB(255, 0, 255));
	this->pos = pos;
	this->size.x = size.x;
	this->size.y = size.y;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

void Effect::Update()
{
	if (!isDead)
	{
		currTime += TimeManager::GetInstance()->GetDeltaTime();
		if (currTime > 0.1f)
		{
			currTime = 0;
			currFrame++;
		}
		if (image && currFrame >= image->GetMaxFrameX() - 1)
			isDead = true;
	}
}

void Effect::Render(HDC hdc)
{
	if (image)
		image->TestFrameRender(hdc, 
			pos.x - size.x / 2 - offsetX, pos.y - size.y / 2 - offsetY,
			pos.x + size.x / 2 + offsetX, size.y + offsetY,
			currFrame, 0, false);
}

void Effect::Release()
{
	//if (image)
	//{
	//	//image->Release();
	//	delete image;
	//	image = nullptr;
	//}
}
