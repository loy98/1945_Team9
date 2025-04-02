#pragma once
#include "GameObject.h"
#include "config.h"
class Missile;
class Image;
class MissileManager;

class Player : public GameObject
{
private:
	enum PlayerState
	{
		Idle,
		MoveLeft,
		MoveRight,
		PlayerStateLength
	};
	FPOINT dir{ 1, 1 };
	float damage;
	float moveSpeed;

	int idleCurrFrame;
	int moveCurrFrame;
	float animIdleCurrTime;
	float animMoveCurrTime;
	vector<Image*> imageList{ PlayerStateLength, nullptr};

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

	PlayerState state;
public:
	void Init();	
	void Release();	
	void Update();	
	void Render(HDC hdc);

	void LevelUp(ItemType type);
	void Move();
	void Fire(MissileType type);
	void AddMissile(GameObject* owner, MissileType type, FPOINT pos, float angle, float speed);
	void Dead();

	Player();
	~Player();
};

