#include "UiManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "Image.h"
#include "Player.h"

UiManager::UiManager()
{
}

UiManager::~UiManager()
{
}

void UiManager::Init(Player* player)
{
	this->player = player;
	life = player->GetLife();
	currTime = 0.0f; 
	currFrame = 0;
	ImageManager::GetInstance()->AddImage(
		L"GameOver", L"Image\\UI\\GameOver.bmp", 136, 16, 1, 1, false, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		L"Continue", L"Image\\UI\\Continue.bmp", 72, 11, 1, 1, false, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		L"InsertCoin", L"Image\\UI\\InsertCoin.bmp", 138, 16, 1, 1, false, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		L"Numbers", L"Image\\UI\\Numbers.bmp", 180, 16, 10, 1, false, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		L"Start", L"Image\\UI\\Start.bmp", 800, 900, 1, 1, false, true, RGB(255, 0, 255)); 
	ImageManager::GetInstance()->AddImage(
		L"StageNumber", L"Image\\UI\\StageNumber.bmp", 41, 23, 1, 1, false, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(
		L"Life", L"Image\\UI\\Life.bmp", 222, 98, 3, 1, false, true, RGB(255, 0, 255));
}

void UiManager::Update(GameState state)
{
	currTime += TimeManager::GetInstance()->GetDeltaTime();
	switch (state)
	{
	case GameState::Start:
		if (currFrame > 1)
		{	
			currFrame = 0;
			return;
		}
		break;
	case GameState::Play:
		life = player->GetLife();
		return;
	case GameState::Gameover:
		if (currFrame >= 10) return;
		break;
	case GameState::Clear:
		return;
	}

	if (currTime >= 1.0f)
	{
		currTime = 0;
		currFrame++;
	}

	
}

void UiManager::Render(HDC hdc, GameState state)
{
	switch (state)
	{
	case GameState::Start:
		ImageManager::GetInstance()->FindImage(L"Start")->TestFrameRender(
			hdc, 0, 0, WINSIZE_X, WINSIZE_Y, 0, 0, false);
		ImageManager::GetInstance()->FindImage(L"InsertCoin")->TestFrameRender(
			hdc, 130, 650, 450, 50, currFrame, 0, false);
		return;
	case GameState::Play:
		ImageManager::GetInstance()->FindImage(L"StageNumber")->TestFrameRender(
			hdc, 280, 20, 320, 20, 0, 0, false);
		ImageManager::GetInstance()->FindImage(L"Life")->TestFrameRender(
			hdc, 20, 10, 100, 80, life, 0, false);
		return;
	case GameState::Gameover:
		ImageManager::GetInstance()->FindImage(L"GameOver")->TestFrameRender(
			hdc, 100, 300, 500, 100, 0, 0, false);
		ImageManager::GetInstance()->FindImage(L"Continue")->TestFrameRender(
			hdc, 180, 450, 320, 50, 0, 0, false);
		ImageManager::GetInstance()->FindImage(L"Numbers")->TestFrameRender(
			hdc, 350, 450, 400, 50, 10 - currFrame, 0, false);
		ImageManager::GetInstance()->FindImage(L"InsertCoin")->TestFrameRender(
			hdc, 150, 520, 450, 30, 0, 0, false);
		return;
	case GameState::Clear:
		return;
	}
}

void UiManager::Release()
{
	ReleaseInstance();
}

void UiManager::ResetCurDatas()
{
	currTime = 0.0f;
	currFrame = 0;
}
