#include "DiagonalEnemy.h"

DiagonalEnemy::DiagonalEnemy()
{
}

DiagonalEnemy::~DiagonalEnemy()
{
}

void DiagonalEnemy::Init(float posX, float posY)
{
	Super::Init(posX, posY);
}

void DiagonalEnemy::Release()
{
	Super::Release();
}

void DiagonalEnemy::Update()
{
	Super::Update();
}

void DiagonalEnemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void DiagonalEnemy::Reset(FPOINT pos)
{
	isAlive = true;
	this->pos = pos;

}

void DiagonalEnemy::Move()
{
	Super::Move();
}
