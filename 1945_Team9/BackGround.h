#pragma once
class Image;
class BackGround
{
private:
	Image* currentGround;
	Image* nextGround;
	Image* currentUnderGround;
	Image* nextUnderGround;

	Image* groundCamera;
	Image* underGroundCamera;

	float groundMoveSpeed;
	float underGroundMoveSpeed;

	float groundCameraY;
	float underGroundCameraY;

	float time;

	wchar_t szText[128];

	void SwapGround(Image* current, Image* next);
public:
	void Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

};

