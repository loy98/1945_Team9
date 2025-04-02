#include "NormalMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"
#include "Image.h"

void NormalMissile::Init()
{
	pos = { 0, 0 };
	isActived = false;
	moveSpeed = 150.0f;
	angle = DEG_TO_RAD(90.0f); //enemyMissile 실험 끝나면 DEG_TO 뺴기 + controller도 확인

	size = { 20,20 };
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);		// collision

	moveSpeed = 500.0f;
	animationFrame = 0;
	missileType = MissileType::Normal;

	image = ImageManager::GetInstance()->AddImage(L"1945bullet", TEXT("Image\\1945bulletTest.bmp"), 33, 33, 1, 1, false,true, RGB(248, 0, 248));
	
	controller = new NormalController();
}

void NormalMissile::Release()
{
	Super::Release();
}

void NormalMissile::Update()
{
	Super::Update();		// 미사일 이동 후 pos도 업데이트해줌, isactived,collison 
	//controller->Move(this);
	UpdateRectAtCenter(rc, pos);

	//if (IsOutofScreen())
	//{
	//	isActived = false;
	//}

	if (IsOutofScreen())
	{
		isActived = false;
	}
	if (isCollision)
		isActived = false;
}

void NormalMissile::Render(HDC hdc, bool isFlip)
{
	if (isActived)
	{
		Super::Render(hdc, isFlip);		// collider
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0, isFlip);
		//RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	}

}


//void NormalMissile::ReLoad(FPOINT pos) // 재장전? 살아있다. 
//{
//	this->pos = pos;
//	isActived = true;
//	isCollision = false;
//}

//void NormalMissile::ReLoad(FPOINT pos)
//{
//	this->pos = pos;
//	isActived = true;
//	isCollision = false;
//	angle = DEG_TO_RAD(90.0f); //enemyMissile 실험 끝나면 DEG_TO 뺴기 + controller도 확인
//}


//void NormalMissile::Move()
//{
//	if (isActived)
//	{
//		controller->Move(this);
//	}
//}
