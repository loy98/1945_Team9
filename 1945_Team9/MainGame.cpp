#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Player.h"
#include "MissileManager.h"
#include "CollisionManager.h"
#include "Timer.h"
#include "BackGround.h"
#include "ItemManager.h"
#include "EffectManager.h"
#include "UiManager.h"

/*
	실습1. 이오리 집에 보내기
	실습2. 배경 바꾸기 (킹오파 애니메이션 배경)
*/

void MainGame::Init()
{

	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}

	rocket = new Player();
	rocket->Init();

	KeyManager::GetInstance()->Init();
	ImageManager::GetInstance()->Init();
	EffectManager::GetInstance()->Init();
	UiManager::GetInstance()->Init(rocket);

	enemyManager = new EnemyManager(rocket);
	enemyManager->Init();

	backGround = new BackGround();
	backGround->Init();

	//아이템 확인용
	//ItemManager::GetInstance()->AddItem(ItemType::Laser, { 300, 500 }, { 20, 20 });
	
}

void MainGame::Release()
{
	if (enemyManager)
	{
		enemyManager->Release();
		delete enemyManager;
		enemyManager = nullptr;
	}

	if (rocket)
	{
		rocket->Release();
		delete rocket;
		rocket = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	if (backGround)
	{
		backGround->Release();
		backGround = nullptr;
	}

	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();
	EffectManager::GetInstance()->Release();
	CollisionManager::GetInstance()->Release();

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	backGround->Update();
	
	switch (state)
	{
	case GameState::Start:
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
		{
			state = GameState::Play;
		}
		break;
	case GameState::Play:
		if (rocket) rocket->Update();
		if (rocket->GetLife() <= 0)
		{
			state = GameState::Gameover;
			UiManager::GetInstance()->ResetCurDatas();
		}
		if (enemyManager) enemyManager->Update();

		EffectManager::GetInstance()->Update();
		CollisionManager::GetInstance()->Update();
		ItemManager::GetInstance()->Update();
		break;
	case GameState::Gameover:
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
		{
			Release();
			Init();
			state = GameState::Play;
		}
		break;
	case GameState::Clear:
		break;
	default:
		break;
	}
	UiManager::GetInstance()->Update(state);
}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();
	backGround->Render(hBackBufferDC);
	UiManager::GetInstance()->Render(hBackBufferDC, state);

	switch (state)
	{
	case GameState::Start:
		break;
	case GameState::Play:
		if (enemyManager) enemyManager->Render(hBackBufferDC);
		if (rocket) rocket->Render(hBackBufferDC);
		ItemManager::GetInstance()->Render(hBackBufferDC);
		EffectManager::GetInstance()->Render(hBackBufferDC);
		break;
	case GameState::Gameover:
		break;
	case GameState::Clear:
		break;
	default:
		break;
	}

	//wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	//TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

	//TimeManager::GetInstance()->Render(hBackBufferDC);
	// 백버퍼에 있는 내용을 메인 hdc에 복사
	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		srand(static_cast<unsigned int>(time(nullptr)));
		break;
	case WM_TIMER:
		break;
	case WM_KEYDOWN:
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);
		break;
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
