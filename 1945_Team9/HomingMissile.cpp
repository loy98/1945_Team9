#include "HomingMissile.h"
#include "Image.h"
#include "CommonFunction.h"
#include "MissileController.h"

void HomingMissile::Init()
{
	pos = { 0, 0 };
	isActived = false;
	angle = DEG_TO_RAD(90.0f);

	size = { 20,20 };
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);

	moveSpeed = 500.0f;
	currentFrame = 0;
	maxFrame = currentFrame + 1;

	missileType = MissileType::Homing;

	idle = ImageManager::GetInstance()->AddImage(L"HomingMissileIdle", TEXT("Image/HomingMissile/Idle.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255));
	left = ImageManager::GetInstance()->AddImage(L"HomingMissileLeft", TEXT("Image/HomingMissile/Left.bmp"), 240, 15, 16, 1, false, true, RGB(255, 0, 255));
	right = ImageManager::GetInstance()->AddImage(L"HomingMissileRight", TEXT("Image/HomingMissile/Right.bmp"), 240, 15, 16, 1, false, true, RGB(255, 0, 255));
	controller = new HomingController();
	
	currentAnimation = idle;

	prevAngle = DEG_TO_RAD(90.0f);
	
	elapsedTime = 0.0f;

	target = nullptr;

}

void HomingMissile::Release()
{
	//Super::Release();
}

void HomingMissile::Update()
{
	elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	// currpos 업데이트
	// 애니메이션프레임 업데이트
	Super::Update();
	
	UpdateRectAtCenter(rc, pos);		// 충돌 업데이트!

	if (!isActived) target = nullptr;

	if (isCollision)
		isActived = false;	// 이거 collision manager에서 함

	if(elapsedTime >= 0.5f )
	{
		currentFrame++;
		if (currentFrame > maxFrame)
		{
			currentFrame = maxFrame-1;
		}
		currAngle = angle;

		UpdateImage();

		elapsedTime = 0.0f;
	}
}

void HomingMissile::Render(HDC hdc, bool isFlip)
{
	
	Super::Render(hdc, isFlip);	// collision
	currentAnimation->FrameRender(hdc, pos.x, pos.y, currentFrame, 0, isFlip);
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
	// 예전 위치와 현재 위치 비교->각도 비교
	// 위로 가는데 왼쪽으로 향하면 left 이미지
	// 위로 가는데 오른쪽으로 향하면 right 이미지
	//
	float move = prevAngle - currAngle;

	if (move <= -0.5f)		// 왼쪽 회전
	{
		MoveToTherLeft();
	}
	else if (move >= 0.5f)	// 오른쪽 회전
	{
		MoveToTheRight();
	}
	else
	{

	}
	prevAngle = currAngle;
}

void HomingMissile::MoveToTheRight()
{
	if (currentAnimation == idle)
	{
		currentAnimation = right;
		currentFrame = 0;
	}
	else if (currentAnimation == left)
	{
		if (maxFrame == 1)
		{
			currentAnimation = idle;
			currentFrame = 0;
		}
		else
		{
			currentFrame = maxFrame -2;
		}
	}
	else // 오른쪽 프레임
	{
		if (maxFrame == 15)	// 마지막 프레임
		{
			currentAnimation = left;
			currentFrame = 2 * 7;
		}
		else
		{
			currentFrame = maxFrame+1;
		}
	}
	maxFrame = currentFrame + 1;
}

void HomingMissile::MoveToTherLeft()
{
	if (currentAnimation == idle)
	{
		currentAnimation = left;
		currentFrame = 0;
	}
	else if (currentAnimation == right)
	{
		if (maxFrame == 15)	// 마지막 프레임
		{
			currentAnimation = idle;
			currentFrame = 0;
		}
		else
		{
			currentFrame = maxFrame -2;
		}
	}
	else // 왼쪽 프레임
	{
		if (maxFrame == 15)
		{
			currentAnimation = right;
			currentFrame = 2 * 7;
		}
		else
		{
			currentFrame = maxFrame+1;
		}
	}
	maxFrame = currentFrame + 1;
}
