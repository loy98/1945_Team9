#include "HomingItem.h"

HomingItem::HomingItem()
{
}

HomingItem::~HomingItem()
{
}

void HomingItem::Init(FPOINT pos, FPOINT size)
{
	Super::Init(pos, size);
	maxAnimationFrame = 8;

	offsetX = 20;
	offsetY = 0;
	image = ImageManager::GetInstance()->AddImage(
		L"HomingItem", TEXT("Image\\Item\\HomingItem.bmp"), 256, 14, 8, 1, false, true, RGB(248, 0, 248));
}

void HomingItem::Update()
{
	Super::Update();
}

void HomingItem::Release()
{
	Super::Release();
}

void HomingItem::Render(HDC hdc)
{
	Super::Render(hdc);
}
