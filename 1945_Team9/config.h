#pragma once
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Msimg32.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
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

	void Normalize() {
		float length = sqrt(x * x + y * y);
		if (length != 0) {
			x /= length;
			y /= length;
		}
	}
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
	Laser,
	Straight,
	Homing,
	MissileTypeLength
};
enum class CollisionGroup
{
	Player,
	Enemy,
	Item,
	GroupLength
};
enum class ObjectType
{
	Player,
	Enemy,
	Missile,
	Item,
	TypeLength
};
enum class ItemType
{
	Normal,
	Laser,
	Homing,
	Straight,
	ItemTypeLength
};
enum class EnemyType
{
	Diagonal,
	EnemyTypeLength
};
struct Size
{
	float x;
	float y;
};