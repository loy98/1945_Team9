#pragma once
#include "config.h"
#include "Singleton.h"

class Effect;
class EffectManager : public Singleton<EffectManager>
{
public:
	EffectManager();
	~EffectManager();

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void AddEffect(Effect* effect);
	void DeleteEffect(Effect* effect);
private:
	vector<Effect*> vecEffect;
};

