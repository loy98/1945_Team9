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
	int size;
	float damage;
	float moveSpeed;
	string name;
	RECT rcCollision;
	Image* image;

	// ����
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;	// ���� : ��(degree)	0 ~ 180		~	360
						//	    : ����(radian)0f ~ 3.14f	~	6.28f
	// �̻���
	int missileCount;
	float missileSpeed;
	bool LaserLaunched = false;
	//Missile* missile[10];

	MissileManager* missileManager;

public:
	void Init();	
	void Release();	
	void Update();	
	void Render(HDC hdc);

	void Move();
	void Fire(MissileType type);
	void RotateBarrel(float angle);
	void Dead();

	
	inline int GetMissileCount() { return missileCount; }
	//inline Missile* GetMissiles() { return missiles; }
	inline void SetBarrelAngle(float angle) { this->barrelAngle = angle; }

	Tank();
	~Tank();
};

