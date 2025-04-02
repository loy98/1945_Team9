#pragma once
#include "config.h"

class Collider;
class GameObject
{
public:
	void Init();		// 멤버 변수의 초기화, 메모리 할당
	void Release();		// 메모리 해제
	void Update();		// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc);	// 프레임 단위로 출력(이미지, 텍스트 등)

	inline FPOINT GetPos() { return pos; }
	void AddCollider(Collider* collider);
	void SetIsCollision(bool isCollision) { this->isCollision = isCollision; }
	bool GetIsCollision() { return isCollision; }
	ObjectType GetObjectType() { return type; }
	virtual RECT GetRect() { return rc; }
	Size GetSize() { return size; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return isAlive; }

	GameObject();
	~GameObject();
protected:
	FPOINT pos;
	vector<Collider*> colliderList;
	ObjectType type;
	RECT rc;
	Size size;

	bool isCollision;
	bool isAlive;
};
