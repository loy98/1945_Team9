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

	// enemyMissile test ������ radian ��� ����
	//pos.x += moveSpeed * time * cosf(DEG_TO_RAD(angle));
	//pos.y -= moveSpeed * time * sinf(DEG_TO_RAD(angle));

	missile->SetPos(pos);		// �̵��Ѹ�ŭ pos ��ȯ
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

	float angle = GetAngle(missile->GetPos(),missile->GetTargetPos());	// ����

	pos.x += moveSpeed * time * cosf(angle);
	pos.y -= moveSpeed * time * sinf(angle);

	missile->SetPos(pos);		//

	// enemy�� ���������� ������.
	// ���� ���� �����ͷ� ��� �ٲ���(prevpos�� currpos�޾Ƽ� ���) �׷��� �ٲ۰� ���⼱ �����̱⸸ �Ѵ�.
	// �� ��ġ. ������ ���ٰ� ���� ������? ����ġ ���� �����ؾ� ��.
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

	// enemyMissile test ������ radian ��� ����
	//pos.x += moveSpeed * time * cosf(DEG_TO_RAD(angle));
	//pos.y -= moveSpeed * time * sinf(DEG_TO_RAD(angle));

	missile->SetPos(pos);
}
