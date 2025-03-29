#include "TimeManager.h"
#include "Timer.h"
void TimeManager::Init()
{
	timer = new Timer();
	timer->Init();
}

void TimeManager::Release()
{
	if (timer)
	{
		timer->Release();
		delete timer;
		timer = nullptr;
	}
	
}

void TimeManager::Update()
{
	if (timer)
		timer->Tick();
}

void TimeManager::Render(HDC hdc)
{
	if (timer)
	{
		wsprintf(szText, L"fps : %d, delta : %f", timer->GetFPS(), timer->GetDeltaTime());
		TextOut(hdc, WINSIZE_X - 130, 20, szText, wcslen(szText));
	}
}

float TimeManager::GetDeltaTime()
{
	if (timer) return timer->GetDeltaTime();
	return 0.0f;
}
