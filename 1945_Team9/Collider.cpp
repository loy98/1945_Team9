#include "Collider.h"
#include "GameObject.h"
Collider::Collider(GameObject* owner, FPOINT pos) : owner(owner), pos(pos)
{
	rc = owner->GetRect();
}

Collider::~Collider()
{
}

void Collider::Update()
{
	//if (isCollision) return;
	pos = owner->GetPos();
	rc = owner->GetRect();
	isCollision = owner->GetIsCollision();
}

void Collider::Render(HDC hdc)
{
	if (!showDebug) return;
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	if (owner->GetIsCollision())
	{
		myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, myPen);
	}	
	else
	{	
		myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		oldPen = (HPEN)SelectObject(hdc, myPen);
	}

	// 숫자 하드코딩이 아니라 가져오는 식으로 바꿔야함
	Rectangle(hdc, owner->GetRect().left, owner->GetRect().top,
		owner->GetRect().right, owner->GetRect().bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
}

void Collider::Release()
{
}

bool Collider::CheckCollision(Collider* other)
{
	RECT r1 = this->GetRect();
	RECT r2 = other->GetRect();
	RECT intersect = {};

	return ::IntersectRect(&intersect, &r1, &r2);
}
