#include "HomingMissile.h"
#include "Image.h"

void HomingMissile::Init()
{
	isActived;
	moveSpeed;
	angle;
	destination;

	owner;
	controller;
	idle;
	animationFrame;
	left;
	right;
	currPos;
	prevPos;
}

void HomingMissile::Release()
{
}

void HomingMissile::Update()
{
	// currpos ������Ʈ
}

void HomingMissile::Render(HDC hdc, bool isFlip)
{
}

void HomingMissile::ReLoad(FPOINT pos)
{
}

void HomingMissile::Move()
{
}

void HomingMissile::UpdateImage()
{
	// ���� ��ġ�� ���� ��ġ ��
	// ���� ���µ� �������� ���ϸ� left �̹��� ����
	// ���� ���µ� ���������� ���ϸ� right �̹��� ����
	// �� ���¸� ������ idle�� �� ��ģ��.
	//

	prevPos = currPos;
}
