#include "MissileController.h"
#include "Missile.h"
MissileController::MissileController()
{
}

MissileController::~MissileController()
{
}

void MissileController::Move(Missile* missile)
{
}

NormalController::NormalController()
{
}

NormalController::~NormalController()
{
}

void NormalController::Move(Missile* missile)
{
	float time = TimeManager::GetInstance()->GetDeltaTime();
	FPOINT pos = missile->GetPos();
	float moveSpeed = missile->GetMoveSpeed();
	float angle = missile->GetAngle();
	float slowSpeed = moveSpeed / 2.0f;
	float addSpeed = 0.01f;
	

	for (int i = 0; i < 5; i++)
	{
		moveSpeed += addSpeed * 0.01f;
		pos.x += moveSpeed * time * cosf(DEG_TO_RAD(angle));
		pos.y -= moveSpeed * time * sinf(DEG_TO_RAD(angle));
	}
	
	missile->SetPos(pos);
}

LaserController::LaserController()
{
}

LaserController::~LaserController()
{
}
