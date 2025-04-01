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
	// currpos 업데이트
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
	// 예전 위치와 현재 위치 비교
	// 위로 가는데 왼쪽으로 향하면 left 이미지 벡터
	// 위로 가는데 오른쪽으로 향하면 right 이미지 벡터
	// 두 상태를 오갈땐 idle을 꼭 거친다.
	//

	prevPos = currPos;
}
