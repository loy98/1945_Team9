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
