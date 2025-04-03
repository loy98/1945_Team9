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
	maxFrame = currentFrame + 1;

	missileType = MissileType::Homing;

	idle = ImageManager::GetInstance()->AddImage(L"HomingMissileIdle", TEXT("Image/HomingMissile/Idle.bmp"), 30, 15, 2, 1, false, true, RGB(255, 0, 255));
	left = ImageManager::GetInstance()->AddImage(L"HomingMissileLeft", TEXT("Image/HomingMissile/Left.bmp"), 240, 15, 16, 1, false, true, RGB(255, 0, 255));
	right = ImageManager::GetInstance()->AddImage(L"HomingMissileRight", TEXT("Image/HomingMissile/Right.bmp"), 240, 15, 16, 1, false, true, RGB(255, 0, 255));
	controller = new HomingController();
	
	currentAnimation = idle;
	prevPos = {300, 600};

	elapsedTime = 0.0f;

}

void HomingMissile::Release()
{
	//Super::Release();
}

void HomingMissile::Update()
{
	elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	// currpos ������Ʈ
	// �ִϸ��̼������� ������Ʈ
	Super::Update();
	currPos = pos;
	
	//UpdateImage();
	UpdateRectAtCenter(rc, pos);		// �浹 ������Ʈ!

	if (isCollision)
		isActived = false;
	if(elapsedTime >= 0.5f )
	{
		UpdateImage();

		currentFrame++;
		if (currentFrame > maxFrame)
		{
			currentFrame = 0;
		}

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
	// ���� ��ġ�� ���� ��ġ ��
	// ���� ���µ� �������� ���ϸ� left �̹���
	// ���� ���µ� ���������� ���ϸ� right �̹���
	// �� ���¸� ������ idle�� ��ģ��.
	//
	float deg = (float)RAD_TO_DEG(::GetAngle(prevPos, currPos));
	
	if (deg > 105.0f)		// ���� 15�� �̻� ȸ��
	{
		MoveToTherLeft();
	}
	else if (deg < 75.0f)		// ������ 15�� �̻� ȸ��
	{
		MoveToTheRight();
	}
	else	// �״��
	{
	}

	prevPos = currPos;
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
			currentFrame -= 2;
		}
	}
	else // ������ ������
	{
		if (maxFrame == 15)	// ������ ������
		{
			currentAnimation = left;
			currentFrame = 2 * 7;
		}
		else
		{
			currentFrame += 2;
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
		if (maxFrame == 15)	// ������ ������
		{
			currentAnimation = idle;
			currentFrame = 0;
		}
		else
		{
			currentFrame -= 2;
		}
	}
	else // ���� ������
	{
		if (maxFrame == 15)
		{
			currentAnimation = right;
			currentFrame = 2 * 7;
		}
		else
		{
			currentFrame += 2;
		}
	}
	maxFrame = currentFrame + 1;
}
