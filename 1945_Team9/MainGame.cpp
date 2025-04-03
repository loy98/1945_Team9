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

/*
	�ǽ�1. �̿��� ���� ������
	�ǽ�2. ��� �ٲٱ� (ŷ���� �ִϸ��̼� ���)
*/

void MainGame::Init()
{
	KeyManager::GetInstance()->Init();
	ImageManager::GetInstance()->Init();
	EffectManager::GetInstance()->Init();

	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("����� ���� ����"), TEXT("���"), MB_OK);
	}

	rocket = new Player();

	rocket->Init();

	enemyManager = new EnemyManager(rocket);
	enemyManager->Init();

	backGround = new BackGround();
	backGround->Init();

	//gameover Ȯ�ο�
	ImageManager::GetInstance()->AddImage(
		L"GameOver", L"Image\\GameOver.bmp", 136, 16, 1, 1, false, true, RGB(255, 0, 255));

	//������ Ȯ�ο�
	ItemManager::GetInstance()->AddItem(ItemType::Laser, { 300, 500 }, { 20, 20 });
	
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
	if (GameOver)
	{
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
		{
			Release();
			Init();
			GameOver = false;
		}
		else
			return;
	}
	//InvalidateRect(g_hWnd, NULL, false);
	if (rocket) rocket->Update();
	if (rocket->GetLife() <= 0)
	{
		GameOver = true;
	}

	if (enemyManager) enemyManager->Update();


	EffectManager::GetInstance()->Update();
	CollisionManager::GetInstance()->Update();
	ItemManager::GetInstance()->Update();
}

void MainGame::Render()
{
	// ����ۿ� ���� ����
	HDC hBackBufferDC = backBuffer->GetMemDC();


	backGround->Render(hBackBufferDC);
	if (GameOver)
	{
		ImageManager::GetInstance()->FindImage(L"GameOver")
			->TestFrameRender(hBackBufferDC,
				100, 300, 500, 100, 0, 0, false);
		backBuffer->Render(hdc);
		return;
	}
	if (enemyManager) enemyManager->Render(hBackBufferDC);
	if (rocket) rocket->Render(hBackBufferDC);
	ItemManager::GetInstance()->Render(hBackBufferDC);
	EffectManager::GetInstance()->Render(hBackBufferDC);

	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

	TimeManager::GetInstance()->Render(hBackBufferDC);
	// ����ۿ� �ִ� ������ ���� hdc�� ����
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
