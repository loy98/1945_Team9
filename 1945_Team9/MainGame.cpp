#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Tank.h"
#include "MissileManager.h"
#include "CollisionManager.h"
#include "Timer.h"

/*
	실습1. 이오리 집에 보내기
	실습2. 배경 바꾸기 (킹오파 애니메이션 배경)
*/

void MainGame::Init()
{
	KeyManager::GetInstance()->Init();
	ImageManager::GetInstance()->Init();

	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}
	//backGround = new Image();
	//if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	//{
	//	MessageBox(g_hWnd,
	//		TEXT("Image/BackGround.bmp 생성 실패"), TEXT("경고"), MB_OK);
	//}
	enemyManager = new EnemyManager();
	enemyManager->Init();

	rocket = new Tank();
	rocket->Init();
	
	// Test
	ground = ImageManager::GetInstance()->AddImage(
		L"ground", TEXT("Image\\1945BackGround1.bmp"), 320, 6114, 1, 1, true, RGB(255, 0, 255));

	tempImage = ImageManager::GetInstance()->AddImage(
		L"groundFlip", TEXT("Image\\1945BackGround1Filp.bmp"), 320, 6114, 1, 1, true, RGB(255, 0, 255));

	underGround = ImageManager::GetInstance()->AddImage(
		L"underGround", TEXT("Image\\1945BackGround2.bmp"), 320, 6114, 1, 1, true, RGB(255, 0, 255));

	groundMoveSpeed = 1.0f;
	underGroundMoveSpeed = 0.8f;

	groundFrameY = 0.0f;
	underGroundFrameY = 0.0f;

	elapsedTime = 0.0f;

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

	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	//InvalidateRect(g_hWnd, NULL, false);

	if (enemyManager) enemyManager->Update();
	if (rocket) rocket->Update();
	CollisionManager::GetInstance()->Update();

	groundFrameY += groundMoveSpeed * TimeManager::GetInstance()->GetDeltaTime();
	underGroundFrameY += underGroundMoveSpeed * TimeManager::GetInstance()->GetDeltaTime();

	if (((groundFrameY + 1) * 600 >= 6114))
	{
		// 그라운드 이미지 교체
		tempImage = ImageManager::GetInstance()->FindImage(L"ground");

		ground = (tempImage == ground) ?
			ImageManager::GetInstance()->FindImage(L"groundFlip") : ImageManager::GetInstance()->FindImage(L"ground");

		groundFrameY = 0;
		underGroundFrameY = 0;
	}
}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	//backGround->Render(hBackBufferDC);
	if (enemyManager) enemyManager->Render(hBackBufferDC);
	if (rocket) rocket->Render(hBackBufferDC);

	// Test
	underGround->TestRender(hBackBufferDC, 0, 0, underGroundFrameY, false);
	ground->TestRender(hBackBufferDC, 0, 0, groundFrameY, false);

	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

	TimeManager::GetInstance()->Render(hBackBufferDC);
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
