#include "MissileManager.h"
#include "Missile.h"
#include "NormalMissile.h"
#include "MissileFactory.h"

MissileManager::MissileManager()
{
}

MissileManager::~MissileManager()
{
}

void MissileManager::Init()
{
	MissileList.reserve(8);
	factoryList[(int)(MissileType::Normal)] = new NormalMissileFactory();
	factoryList[(int)(MissileType::Laser)] = new LaserMissileFactory();
}

void MissileManager::Release()
{
	for (auto& missile : MissileList)
	{
		if (missile)
		{
			missile->Release();
			delete missile;
			missile = nullptr;
		}
	}
	for (auto& factory : factoryList)
	{
		if (factory)
		{
			delete factory;
			factory = nullptr;
		}
	}
}

void MissileManager::Update()
{
	for (auto& missile : MissileList)
	{
		if (missile && missile->GetIsActived())
			missile->Update();
	}
}

void MissileManager::Render(HDC hdc, bool isFlip)
{
	for (auto missile : MissileList)
	{
		if (missile)
			missile->Render(hdc, isFlip);
	}
}

void MissileManager::Launch(FPOINT pos)
{
	for (auto missile : MissileList)
	{
		if (missile && !missile->GetIsActived())
		{
			missile->ReLoad(pos);
			break;
		}
	}
}

void MissileManager::AddMissile(Missile* missile)
{
	MissileList.push_back(missile);
}

Missile* MissileManager::CreateMissile(MissileType type, FPOINT pos, float angle, float speed)
{
	switch (type)
	{
	case MissileType::Normal:
		return factoryList[(int)(MissileType::Normal)]->CreateMissile(pos, angle, speed);
	case MissileType::Sin:
		return nullptr;
	case MissileType::Laser:
		return factoryList[(int)(MissileType::Laser)]->CreateMissile(pos, angle, speed);
	}
}
