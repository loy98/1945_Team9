#pragma once
#include "GameObject.h"
#include "config.h"
class Missile;
class MissileFactory;
class MissileManager : public GameObject
{
public:
	MissileManager();
	~MissileManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Launch(FPOINT pos);

	void AddMissile(Missile* missile);
	Missile* CreateMissile(MissileType type, FPOINT pos, float angle, float speed);
	const int GetMissileListSize() { return MissileList.size(); }
private:
	vector<Missile*> MissileList;
	vector<MissileFactory*> factoryList{ (int)(MissileType::MissileTypeLength), nullptr };
};

