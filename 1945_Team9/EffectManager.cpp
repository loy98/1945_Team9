#include "EffectManager.h"
#include "ImageManager.h"
#include "Effect.h"
EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Init()
{
	ImageManager::GetInstance()->AddImage(L"EnemyDie", L"Image\\EnemyDie.bmp", 975, 64, 15, 1, false, true, RGB(255, 0, 255));
}

void EffectManager::Update()
{
	for (auto effect : vecEffect)
	{
		if (effect)
		{
			effect->Update();
			if (effect->GetIsDead())
			{
				effect->Release();
				DeleteEffect(effect);
			}
		}
	}
}

void EffectManager::Render(HDC hdc)
{
	for (auto effect : vecEffect)
	{
		if (effect)
		{
			effect->Render(hdc);
		}
	}
}

void EffectManager::Release()
{
	for (auto effect : vecEffect)
	{
		if (effect)
		{
			effect->Release();
			delete effect;
		}
	}
	vecEffect.clear();
}

void EffectManager::AddEffect(Effect* effect)
{
	vecEffect.push_back(effect);
}

void EffectManager::DeleteEffect(Effect* effect)
{
	auto it = remove(vecEffect.begin(), vecEffect.end(), effect);
	vecEffect.erase(it, vecEffect.end());
}
