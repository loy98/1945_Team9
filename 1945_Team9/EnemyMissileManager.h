#pragma once
#include "MissileManager.h"

class MissileFactory;
class Missile;
class EnemyMissileManager : public MissileManager
{
private:
    vector<Missile*> vecMissileList;

public:
    EnemyMissileManager();
    virtual ~EnemyMissileManager();
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Render(HDC hdc, bool isFlip) override;
    virtual void Launch(FPOINT pos) override;
    virtual void AngleLaunch(FPOINT pos, float angle) override;

    virtual void AddMissile() override;
};