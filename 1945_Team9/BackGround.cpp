#include "BackGround.h"
#include "Image.h"

void BackGround::Init()
{
	currentGround = ImageManager::GetInstance()->AddImage(
		L"ground", TEXT("Image/1945BackGround1.bmp"), 320, 6114, 1, 1, true, RGB(255, 0, 255));

	nextGround = ImageManager::GetInstance()->AddImage(
		L"groundFlip", TEXT("Image/1945BackGround1Filp.bmp"), 320, 6114, 1, 1, true, RGB(255, 0, 255));

	currentUnderGround = ImageManager::GetInstance()->AddImage(
		L"underGround", TEXT("Image/1945BackGround2.bmp"), 320, 6114, 1, 1, true, RGB(255, 0, 255));

	nextUnderGround = ImageManager::GetInstance()->AddImage(
		L"underGroundFlip", TEXT("Image/1945BackGround2Flip.bmp"), 320, 6114, 1, 1, true, RGB(255, 0, 255));

	groundCamera = new Image();
	if (FAILED(groundCamera->Init(WINSIZE_X, WINSIZE_Y, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd,
			TEXT("그라운드 카메라 생성 실패"), TEXT("경고"), MB_OK);
	}

	underGroundCamera = new Image();
	if (FAILED(underGroundCamera->Init(WINSIZE_X, WINSIZE_Y, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd,
			TEXT("언더그라운드 카메라 생성 실패"), TEXT("경고"), MB_OK);
	}

	groundMoveSpeed = 0.5f;
	underGroundMoveSpeed = 0.3f;

	groundCameraY = (WINSIZE_X / 310.f);
	underGroundCameraY = (WINSIZE_X / 310.f);

	time = TimeManager::GetInstance()->GetDeltaTime();
}

void BackGround::Release()
{
	if (currentGround)
	{
		currentGround = nullptr;
	}
	if (nextGround)
	{
		nextGround = nullptr;
	}
	if (currentUnderGround)
	{
		currentUnderGround = nullptr;
	}
}

void BackGround::Update()
{
	time = TimeManager::GetInstance()->GetDeltaTime();
	groundCameraY += groundMoveSpeed * time;
	underGroundCameraY += underGroundMoveSpeed * time;
	// 스왑
	float a = (WINSIZE_X / 310.f);
	Image* g = ImageManager::GetInstance()->FindImage(L"ground");
	Image* gf = ImageManager::GetInstance()->FindImage(L"groundFlip");
	if (groundCameraY >= (6114.0f / WINSIZE_Y)+ (310.0f/WINSIZE_X))     // 첫번째 이미지 다 지나감, 두번째 이미지 WINSIZE_Y만큼 출력
	{
		groundCameraY -= (6114.0f / WINSIZE_Y);
		SwapGround(currentGround, nextGround);
	}

	if (underGroundCameraY >= (6114.0f / WINSIZE_Y) + (310.0f/WINSIZE_X))     // 첫번째 이미지 다 지나감, 두번째 이미지 WINSIZE_Y만큼 출력
	{
		underGroundCameraY -= (6114.0f / WINSIZE_Y);
		SwapGround(currentUnderGround, nextUnderGround);
	}

}

void BackGround::Render(HDC hdc)
{
	underGroundCamera->CameraRender(hdc, currentUnderGround, nextUnderGround, underGroundCameraY);
	groundCamera->CameraRender(hdc, currentGround, nextGround, groundCameraY);

	wsprintf(szText, TEXT("groundFrameY : %d"), (int)groundCameraY);
	TextOut(hdc, 20, 60, szText, wcslen(szText));
}

void BackGround::SwapGround(Image* current, Image* next)
{
	Image temp;
	temp = *current;

	*current = *next;
	*next = temp;
}
