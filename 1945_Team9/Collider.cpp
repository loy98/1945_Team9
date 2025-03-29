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

	// 숫자 하드코딩이 아니라 가져오는 식으로 바꿔야함
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
