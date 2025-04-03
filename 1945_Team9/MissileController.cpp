#include "MissileController.h"
#include "Missile.h"
#include "CommonFunction.h"
MissileController::MissileController()
{
}

MissileController::~MissileController()
{
}
//
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
		
	pos.x += moveSpeed * time * cosf(angle);
	pos.y -= moveSpeed * time * sinf(angle);

	// enemyMissile test 때문에 radian 배고 실험
	//pos.x += moveSpeed * time * cosf(DEG_TO_RAD(angle));
	//pos.y -= moveSpeed * time * sinf(DEG_TO_RAD(angle));

	missile->SetPos(pos);		// 이동한만큼 pos 반환
}
//
LaserController::LaserController()
{
}

LaserController::~LaserController()
{
}

void LaserController::Move(Missile* missile)
{
}
//
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
	float maxSpeed = 900.f;

	if (moveSpeed < maxSpeed)
	{
		moveSpeed += 60 * addSpeed * time;
		missile->SetAddSpeed(addSpeed + 5 * time * addSpeed);
	}

	else if (moveSpeed >= maxSpeed)
	{
		moveSpeed = maxSpeed;
	}

	pos.x += moveSpeed * time * cosf(DEG_TO_RAD(missile->GetAngle()));
	pos.y -= moveSpeed * time * sinf(DEG_TO_RAD(missile->GetAngle()));

	missile->SetMoveSpeed(moveSpeed);
	
	//missile->SetAddSpeed(1.01f * addSpeed);
	missile->SetPos(pos);
}
//
HomingController::HomingController()
{
}

HomingController::~HomingController()
{
}

void HomingController::Move(Missile* missile)
{
	float time = TimeManager::GetInstance()->GetDeltaTime();
	FPOINT pos = missile->GetPos();
	float moveSpeed = missile->GetMoveSpeed();
	//float angle = missile->GetAngle();

	float angle = GetAngle(missile->GetPos(),missile->GetTargetPos());	// 라디안

	pos.x += moveSpeed * time * cosf(angle);
	pos.y -= moveSpeed * time * sinf(angle);

	missile->SetPos(pos);		//

	// enemy의 포지션으로 움직임.
	// 현재 상태 포인터로 계속 바꿔줌(prevpos와 currpos받아서 계산) 그렇게 바꾼걸 여기선 움직이기만 한다.
	// 적 위치. 적한테 가다가 적이 죽으면? 적위치 새로 갱신해야 함.
}

EnemyController::EnemyController()
{
}

EnemyController::~EnemyController()
{
}

void EnemyController::Move(Missile* missile)
{
	float time = TimeManager::GetInstance()->GetDeltaTime();
	FPOINT pos = missile->GetPos();
	float moveSpeed = missile->GetMoveSpeed();
	float angle = missile->GetAngle();

	pos.x += moveSpeed * time * cosf(angle);
	pos.y -= moveSpeed * time * sinf(angle);

	// enemyMissile test 때문에 radian 배고 실험
	//pos.x += moveSpeed * time * cosf(DEG_TO_RAD(angle));
	//pos.y -= moveSpeed * time * sinf(DEG_TO_RAD(angle));

	missile->SetPos(pos);
}
