#pragma once
#include "GameObject.h"
#include "config.h"
class Missile;
class Image;
class MissileManager;
class Player : public GameObject
{
private:
	
	FPOINT dir{ 1, 1 };
	float damage;
	float moveSpeed;
	Image* image;

	// 포신
	FPOINT barrelEnd;
	int barrelSize;
	float fireAngle;	

	// 미사일
	float missileSpeed;
	bool LaserLaunched = false;

	vector<MissileManager*> vecMissileManager;
	vector<MissileManager*>::iterator iter;
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

	Player();
	~Player();
};

