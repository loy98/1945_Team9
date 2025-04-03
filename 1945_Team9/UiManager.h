#pragma once
#include "config.h"
#include "Singleton.h"

class Player;
class UiManager : public Singleton<UiManager>
{
public:
	UiManager();
	~UiManager();

	void Init(Player* player);
	void Update(GameState state);
	void Render(HDC hdc, GameState state);
	void Release();

	void ResetCurDatas();

private:
	Player* player;

	float currTime{};
	int currFrame{};
	int life;
};

