#include "Collider.h"

Collider::Collider(GameObject* owner, FPOINT pos) : owner(owner), pos(pos)
{
	/*isAlive = true;*/
	//test
	isAlive = owner->GetIsAlive();
	rc = owner->GetRect();
	isCollision = owner->GetIsCollision();
}

Collider::~Collider()
{
}

void Collider::Update()
{
	pos = owner->GetPos();
	rc = owner->GetRect();
	isCollision = owner->GetIsCollision();
	isAlive = owner->GetIsAlive();
}

void Collider::Render(HDC hdc)
{
	//collider�� ���ߴܰ迡���� render�Ұ�!
	//if (!isAlive) return;
	//if (!showDebug) return;
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

	// ���� �ϵ��ڵ��� �ƴ϶� �������� ������ �ٲ����
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
