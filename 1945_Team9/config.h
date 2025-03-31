#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"

#define WINSIZE_X	600
#define WINSIZE_Y	800
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

/*
	extern Ű���� : ������ �Լ��� �ٸ� ���Ͽ� ���ǵǾ� �ִ� ���
	����� �˸��� Ű����.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

enum class MissileType
{
	Normal,
	Sin,
	Laser,
	Straight,
	MissileTypeLength
};
enum class CollisionGroup
{
	Player,
	Enemy,
	GroupLength
};
enum class ObjectType
{
	Player,
	Enemy,
	Missile,
	TypeLength
};
struct Size
{
	float x;
	float y;
};