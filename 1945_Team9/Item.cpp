#include "Item.h"
#include "Collider.h"
#include "TimeManager.h"
#include "CommonFunction.h"
#include "CollisionManager.h"
#include "ImageManager.h"
#include "Image.h"
Item::Item()
{
	type = ObjectType::Item;
	
}

Item::~Item()
{
}

void Item::Init(FPOINT pos, FPOINT size)
{
	this->pos = pos;
	moveSpeed = 500.0f;
	angle = 45.0f;
	lifeTime = 12.0f;
	this->size.x = size.x;
	this->size.y = size.y;
	dir = { 1, 1 };
	rc = GetRectAtCenter(pos.x, pos.y, size.x, size.y);
	animationFrame = 0;
	maxAnimationFrame = 7;

	offsetX = 14;
	offsetY = 0;

	Collider* collider = new Collider(this, pos);
	colliderList.push_back(collider);
	CollisionManager::GetInstance()->AddCollider(collider, CollisionGroup::Item);
	image = ImageManager::GetInstance()->AddImage(
		L"LaserItem", TEXT("Image\\LaserItem.bmp"), 224, 14, 7, 1, false, true, RGB(255, 0, 255));
}

void Item::Update()
{
	//isDead = isCollision;
	elapsedTime += TimeManager::GetInstance()->GetDeltaTime();
	elapsedAnimTime += TimeManager::GetInstance()->GetDeltaTime();
	
	if (elapsedAnimTime >= 0.2f)
	{
		elapsedAnimTime = 0;
		animationFrame++;
		if (animationFrame >= maxAnimationFrame)
			animationFrame = 0;
	}
	
	if (isDead)
		return;
	if (pos.x <= 0 || pos.x >= WINSIZE_X) {
		dir.x *= -1;
	}
	if (pos.y <= 0 || pos.y >= WINSIZE_Y) {
		dir.y *= -1;
	}
	pos.x += dir.x * moveSpeed * DEG_TO_RAD(angle) * TimeManager::GetInstance()->GetDeltaTime();
	pos.y += dir.y * moveSpeed * DEG_TO_RAD(angle) * TimeManager::GetInstance()->GetDeltaTime();

	UpdateRectAtCenter(rc, pos);
	for (auto collider : colliderList)
	{
		if (collider)
			collider->Update();
	}
	if (elapsedTime >= lifeTime)
		isDead = true;
}

void Item::Release()
{
	for (auto collider : colliderList)
	{
		if (collider)
		{
			collider->Release();
			delete collider;
			collider = nullptr;
		}
	}
}

void Item::Render(HDC hdc)
{
	if (isDead)	return;
	//RenderRectAtCenter(hdc, pos.x, pos.y, size.x, size.y);
	image->TestFrameRender(hdc, rc.left - offsetX, rc.top, rc.right + offsetX, size.y, animationFrame, 0, false);
	for (auto collider : colliderList)
	{
		if (collider)
			collider->Render(hdc);
	}
}
