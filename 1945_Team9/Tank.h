#pragma once
#include "GameObject.h"
#include "config.h"
class Missile;
class Image;
class MissileManager;
class Tank : public GameObject
{
private:
	
	FPOINT dir{ 1, 0 };
	float damage;
	float moveSpeed;
	Image* image;

	// ����
	FPOINT barrelEnd;
	int barrelSize;
	float fireAngle;	// ���� : ��(degree)	0 ~ 180		~	360
						//	    : ����(radian)0f ~ 3.14f	~	6.28f
	// �̻���
	float missileSpeed;
	bool LaserLaunched = false;

	MissileManager* missileManager;
	CollisionGroup group;
public:
	void Init();	
	void Release();	
	void Update();	
	void Render(HDC hdc);

	void Move();
	void Fire(MissileType type);
	void AddMissile(GameObject* owner, MissileType type, FPOINT pos, float angle, float speed);
	void Dead();

	Tank();
	~Tank();
};

