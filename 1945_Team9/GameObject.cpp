#include "GameObject.h"

void GameObject::Init()
{
	isCollision = false;
}

void GameObject::Release()
{
}

void GameObject::Update()
{
}

void GameObject::Render(HDC hdc)
{
}

void GameObject::AddCollider(Collider* collider)
{
	colliderList.push_back(collider);
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}
