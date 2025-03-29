#include "Collider.h"
#include "GameObject.h"
Collider::Collider()
{


}

Collider::~Collider()
{
}

void Collider::Update()
{
	pos = owner->GetPos();

}

void Collider::Render(HDC hdc)
{
	if (!showDebug) return;
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

	// ���� �ϵ��ڵ��� �ƴ϶� �������� ������ �ٲ����
	Rectangle(hdc, owner->GetPos().x - 100, owner->GetPos().y - 100,
		owner->GetPos().x + 100, owner->GetPos().y + 100);

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
	
	return false;
}
