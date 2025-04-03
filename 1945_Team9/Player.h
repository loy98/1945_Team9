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

	int idleCurrFrame;
	int moveCurrFrame;
	int spawnCurrFrame;
	float animIdleCurrTime;
	float animMoveCurrTime;
	float spawnCurrTime;
	vector<Image*> imageList{ (int)PlayerState::PlayerStateLength, nullptr};

	// ����
	FPOINT barrelEnd;
	int barrelSize;
	float fireAngle;	
	int life;

	// �̻���
	float missileSpeed;
	bool LaserLaunched = false;
	bool isSpawned = true;

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
	int GetLife() { return life; }

	Player();
	~Player();
};

