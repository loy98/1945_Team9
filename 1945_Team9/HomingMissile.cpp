#include "HomingMissile.h"
#include "Image.h"
#include "CommonFunction.h"
#include "MissileController.h"

void HomingMissile::Init()
{
	pos = { 0, 0 };
	isActived = false;
	angle = 90.0f;

	size = { 20,20 };
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);

	moveSpeed = 500.0f;
	currentFrame = 0;
	maxFrame = 2;
	missileType = MissileType::Homing;

	idle = ImageManager::GetInstance()->AddImage(L"HomingMissileIdle", TEXT("HomingMissile/Idle.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255));

	left.push_back(ImageManager::GetInstance()->AddImage(L"HomingL1", TEXT("HomingMissile/l1.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	left.push_back(ImageManager::GetInstance()->AddImage(L"HomingL2", TEXT("HomingMissile/l2.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	left.push_back(ImageManager::GetInstance()->AddImage(L"HomingL3", TEXT("HomingMissile/l3.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	left.push_back(ImageManager::GetInstance()->AddImage(L"HomingL4", TEXT("HomingMissile/l4.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	left.push_back(ImageManager::GetInstance()->AddImage(L"HomingL5", TEXT("HomingMissile/l5.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	left.push_back(ImageManager::GetInstance()->AddImage(L"HomingL6", TEXT("HomingMissile/l6.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	left.push_back(ImageManager::GetInstance()->AddImage(L"HomingL7", TEXT("HomingMissile/l7.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	left.push_back(ImageManager::GetInstance()->AddImage(L"HomingL8", TEXT("HomingMissile/l8.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));

	right.push_back(ImageManager::GetInstance()->AddImage(L"HomingR1", TEXT("HomingMissile/r1.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	right.push_back(ImageManager::GetInstance()->AddImage(L"HomingR2", TEXT("HomingMissile/r2.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	right.push_back(ImageManager::GetInstance()->AddImage(L"HomingR3", TEXT("HomingMissile/r3.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	right.push_back(ImageManager::GetInstance()->AddImage(L"HomingR4", TEXT("HomingMissile/r4.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	right.push_back(ImageManager::GetInstance()->AddImage(L"HomingR5", TEXT("HomingMissile/r5.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	right.push_back(ImageManager::GetInstance()->AddImage(L"HomingR6", TEXT("HomingMissile/r6.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	right.push_back(ImageManager::GetInstance()->AddImage(L"HomingR7", TEXT("HomingMissile/r7.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));
	right.push_back(ImageManager::GetInstance()->AddImage(L"HomingR8", TEXT("HomingMissile/r8.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255)));

	controller = new NormalController();
	
	currentAnimation = idle;
	//idle;
	//animationFrame;
	//left;
	//right;
	//currPos;
	//prevPos;
}

void HomingMissile::Release()
{
}

void HomingMissile::Update()
{
	// currpos 업데이트
	// 애니메이션프레임 업데이트

	currentFrame++;
	if (currentFrame > maxFrame)
	{
		currentFrame = 0;
	}
}

void HomingMissile::Render(HDC hdc, bool isFlip)
{
	Super::Render(hdc, isFlip);	// collision
	currentAnimation->Render(hdc, isFlip);
}

//void HomingMissile::ReLoad(FPOINT pos)
//{
//}
//
//void HomingMissile::Move()
//{
//}

void HomingMissile::UpdateImage()
{
	// 예전 위치와 현재 위치 비교
	// 위로 가는데 왼쪽으로 향하면 left 이미지 벡터
	// 위로 가는데 오른쪽으로 향하면 right 이미지 벡터
	// 두 상태를 오갈땐 idle을 꼭 거친다.
	//

	prevPos = currPos;
}
