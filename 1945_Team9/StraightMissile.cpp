#include "StraightMissile.h"
#include "CommonFunction.h"
#include "MissileController.h"
#include "Image.h"
#include "Tank.h"

StraightMissile::StraightMissile()
{
}

StraightMissile::~StraightMissile()
{
}

void StraightMissile::Init()
{
	Super::Init();

	pos = { 0, 0 };
	isActived = false;
	moveSpeed = 80.0f;
	addSpeed = 10.0f;
	angle = 90.0f;
	size = { 20,40 };
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);
	animationFrame = 0;
	elapsedFrame = 0;
	elapsedTime = 0.0f;
	elapsedMoveTime = 0.0f;
	maxMoveTime = 3.0f;

	vecMissiles.resize(2);
	for (int i = 0; i < 2; i++)
	{
		vecMissiles[i] = new Missile();
		vecMissiles[i]->Init();
	}

	image = ImageManager::GetInstance()->AddImage(L"Bomb_Bullet1", TEXT("Image\\Bomb_Bullet1.bmp"), 240, 64, 8, 1, false, true, RGB(0, 248, 0));
	controller = new StraightController();
}

void StraightMissile::Release()
{

}

void StraightMissile::Update()
{
	elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	elapsedMoveTime += TimeManager::GetInstance()->GetDeltaTime();

	if (elapsedTime > 0.1f)
	{
		elapsedTime = 0.0f;
		animationFrame++;
		if (animationFrame > image->GetMaxFrameX() - 1)	animationFrame = image->GetMaxFrameX() - 1;
	}

	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i]->Update();
		if (vecMissiles[i]->IsOutofScreen())
		{
			vecMissiles[i]->SetIsActived(false);
		}
	}
	
	Super::Update();

	if (true == IsOutofScreen())
	{
		isActived = false;
	}

	/*for (int i = 0; i < vecMissiles.size(); i++)
	{
		if (vecMissiles[i])
		{
			vecMissiles[i]->Update();
			vecMissiles[i]->SetPos(pos);
			if (vecMissiles[i]->IsOutofScreen())
			{
				vecMissiles[i]->SetIsActived(false);
			}
		}
	}*/

	Move();
	UpdateRectAtCenter(rc, pos);
}

void StraightMissile::Render(HDC hdc, bool isFlip)
{
	Super::Render(hdc, isFlip);

	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i]->Render(hdc,isFlip);
	}

	if (isActived)
	{
		image->FrameRender(hdc, pos.x, pos.y, animationFrame, 0, isFlip);
		//RenderEllipseAtCenter(hdc, pos.x, pos.y, size, size);
	}

}

void StraightMissile::ReLoad(FPOINT pos)
{
	this->pos = pos;
	isActived = true;
	isCollision = false;
	angle = 90.0f;
}

void StraightMissile::Move()
{
	if (isActived)
	{
		controller->Move(this);
	}
}
