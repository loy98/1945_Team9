#include "NormalItem.h"

NormalItem::NormalItem()
{
	itemType = ItemType::Normal;
}

NormalItem::~NormalItem()
{
}

void NormalItem::Init(FPOINT pos, FPOINT size)
{
	Super::Init(pos, size);
	maxAnimationFrame = 8;

	offsetX = 20;
	offsetY = 0;
	image = ImageManager::GetInstance()->AddImage(
		L"NormalItem", TEXT("Image\\Item\\NormalItem.bmp"), 256, 14, 8, 1, false, true, RGB(248, 0, 248));
}

void NormalItem::Update()
{
	Super::Update();
}

void NormalItem::Release()
{
	Super::Release();
}

void NormalItem::Render(HDC hdc)
{
	Super::Render(hdc);
}
