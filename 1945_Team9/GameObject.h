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
