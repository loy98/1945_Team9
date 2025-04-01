#include "StraightItem.h"

StraightItem::StraightItem()
{
}

StraightItem::~StraightItem()
{
}

void StraightItem::Init(FPOINT pos, FPOINT size)
{
	Super::Init(pos, size);
	maxAnimationFrame = 8;

	offsetX = 20;
	offsetY = 0;
	image = ImageManager::GetInstance()->AddImage(
		L"StraightItem", TEXT("Image\\Item\\StraightItem.bmp"), 256, 14, 8, 1, false, true, RGB(248, 0, 248));
}

void StraightItem::Update()
{
	Super::Update();
}

void StraightItem::Release()
{
	Super::Release();
}

void StraightItem::Render(HDC hdc)
{
	Super::Render(hdc);
}
