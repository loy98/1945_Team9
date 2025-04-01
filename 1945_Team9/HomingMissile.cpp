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
	animationFrame = 0;
	missileType = MissileType::Homing;

	image = ImageManager::GetInstance()->AddImage(L"1945bullet", TEXT("Image\\1945bulletTest.bmp"), 33, 33, 1, 1, false, true, RGB(248, 0, 248));

	controller = new NormalController();
	
	
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
}

void HomingMissile::Render(HDC hdc, bool isFlip)
{
	Super::Render(hdc, isFlip);	// collision
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
