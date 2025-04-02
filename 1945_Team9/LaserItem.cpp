#include "LaserItem.h"

LaserItem::LaserItem()
{
}

LaserItem::~LaserItem()
{
}

void LaserItem::Init(FPOINT pos, FPOINT size)
{
	Super::Init(pos, size);
	maxAnimationFrame = 7;

	offsetX = 20;
	offsetY = 0;
	image = ImageManager::GetInstance()->AddImage(
		L"LaserItem", TEXT("Image\\Item\\LaserItem.bmp"), 224, 14, 7, 1, false, true, RGB(255, 0, 255));
}

void LaserItem::Update()
{
	Super::Update();
}

void LaserItem::Release()
{
	Super::Release();
}

void LaserItem::Render(HDC hdc)
{
	Super::Render(hdc);
}
