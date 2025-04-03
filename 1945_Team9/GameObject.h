#pragma once
#include "config.h"

class Collider;
class GameObject
{
public:
	void Init();		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update();		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	inline FPOINT GetPos() { return pos; }
	void AddCollider(Collider* collider);
	void SetIsCollision(bool isCollision) { this->isCollision = isCollision; }
	bool GetIsCollision() { return isCollision; }
	ObjectType GetObjectType() { return type; }
	virtual RECT GetRect() { return rc; }
	Size GetSize() { return size; }
	
	//
	void SetTarget(GameObject* target) { this->target = target; }
	FPOINT GetTargetPos() { return target->GetPos(); }
	bool GetTargetIsCollision() { return target->GetIsCollision(); }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return isAlive; }
	void SetPos(FPOINT pos) { this->pos = pos; }

	GameObject();
	~GameObject();
protected:
	FPOINT pos;
	vector<Collider*> colliderList;
	ObjectType type;
	RECT rc;
	Size size;

	//
	GameObject* target;

	bool isCollision;
	bool isAlive;

};
