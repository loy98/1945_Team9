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
		
	pos.x += moveSpeed * time * cosf(DEG_TO_RAD(angle));
	pos.y -= moveSpeed * time * sinf(DEG_TO_RAD(angle));

	missile->SetPos(pos);
}

LaserController::LaserController()
{
}

LaserController::~LaserController()
{
}

StraightController::StraightController()
{
}

StraightController::~StraightController()
{
}

void StraightController::Move(Missile* missile)
{	
	float time = TimeManager::GetInstance()->GetDeltaTime();
	FPOINT pos = missile->GetPos();
	float moveSpeed = missile->GetMoveSpeed();
	float addSpeed = missile->GetAddSpeed();
	float angle = missile->GetAngle();
	float maxSpeed = 1000.f;

	if (moveSpeed < maxSpeed)
	{
		moveSpeed += 60 * addSpeed * time;
		missile->SetAddSpeed(addSpeed + 10 * time * addSpeed);
	}

	else if (moveSpeed >= maxSpeed)
	{
		moveSpeed = maxSpeed;
	}

	pos.x += moveSpeed * time * cosf(DEG_TO_RAD(angle));
	pos.y -= moveSpeed * time * sinf(DEG_TO_RAD(angle));

	missile->SetMoveSpeed(moveSpeed);
	
	//missile->SetAddSpeed(1.01f * addSpeed);
	missile->SetPos(pos);
}