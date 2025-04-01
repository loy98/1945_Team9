#include "ItemManager.h"
#include "Item.h"
#include "CollisionManager.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
}

void ItemManager::Update()
{
	for (auto item : itemList)
	{
		if (item)
		{
			item->Update();
			if (item->GetIsDead())
			{
				DeleteItem(item);
			}
		}
	}
	CollisionManager::GetInstance()->CheckPlayerItemCollision();
}

void ItemManager::Release()
{
	for (auto item : itemList)
	{
		item->Release();
		delete item;
	}
	itemList.clear();
}

void ItemManager::Render(HDC hdc)
{
	for (auto item : itemList)
	{
		if (item)
			item->Render(hdc);
	}
}

void ItemManager::AddItem(FPOINT pos, FPOINT size)
{
	Item* item = new Item();
	item->Init(pos, size);
	itemList.push_back(item);
}

void ItemManager::DeleteItem(Item* item)
{
	auto it = find(itemList.begin(), itemList.end(), item);
	itemList.erase(it);
}

Item* ItemManager::CreateItem(FPOINT pos)
{
	return nullptr;
}

