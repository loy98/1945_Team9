#pragma once
#include "GameObject.h"

class Image;
class EnemyManager;
class Tank;
class Timer;
class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	int mousePosX = 0, mousePosY = 0;
	FPOINT mousePos;
	wchar_t szText[128];

	Image* backBuffer;
	Image* backGround;
	Tank* rocket;

	EnemyManager* enemyManager;

	// Test
	Image* ground;
	Image* underGround;

	Image* tempImage;

	float groundMoveSpeed;
	float groundFrameY;
	float underGroundMoveSpeed;
	float underGroundFrameY;

	float elapsedTime;

public:
	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
					// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	void Release();	
	void Update();	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

