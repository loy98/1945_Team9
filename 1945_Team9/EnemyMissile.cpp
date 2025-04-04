#include "EnemyMissile.h"
#include "CommonFunction.h"

#include "Image.h"
#include "MissileController.h"

void EnemyMissile::Init()
{
	pos = { 0, 0 };
	isActived = false;
	moveSpeed = 150.0f;
	angle = DEG_TO_RAD(90.0f); //enemyMissile ���� ������ DEG_TO ���� + controller�� Ȯ��

	size = { 20,20 };
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);		// collision

	moveSpeed = 150.0f;
	animationFrame = 0;
	missileType = MissileType::Normal;

	image = ImageManager::GetInstance()->AddImage(L"EnemyBullet", TEXT("Image\\EnemyMissile.bmp"), 11, 11, 1, 1, false, true, RGB(255, 255, 255));
	controller = new EnemyController();
}

void EnemyMissile::Release()
{
	//Super::Release();
}

void EnemyMissile::Update()
{
	Super::Update();
	UpdateRectAtCenter(rc, pos);
	if (isCollision)
		isActived = false;
	//isAlive = owner->GetIsAlive();
}

void EnemyMissile::Render(HDC hdc, bool isFlip)
{
	if (isActived)
	{
		//RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
		Super::Render(hdc, isFlip);		// collider
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0, isFlip);
	}
}

