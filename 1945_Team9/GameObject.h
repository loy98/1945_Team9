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
	
	void SetTarget(GameObject* target) { this->target = target; }
	FPOINT GetTargetPos() { return target->GetPos(); }

	GameObject();
	~GameObject();
protected:
	FPOINT pos;
	vector<Collider*> colliderList;
	bool isCollision;
	ObjectType type;
	RECT rc;
	Size size;

	GameObject* target;
};
