#include "ItemManager.h"
#include "Item.h"
#include "NormalItem.h"
#include "LaserItem.h"
#include "HomingItem.h"
#include "StraightItem.h"
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

void ItemManager::AddItem(ItemType type, FPOINT pos, FPOINT size)
{
	Item* item = nullptr;
	switch (type)
	{
	case ItemType::Normal:
		item = new NormalItem();
		break;
	case ItemType::Laser:
		item = new LaserItem();
		break;
	case ItemType::Homing:
		item = new HomingItem();
		break;
	case ItemType::Straight:
		item = new StraightItem();
		break;
	}
	item->Init(pos, size);
	itemList.push_back(item);
}

void ItemManager::DeleteItem(Item* item)
{
	auto it = find(itemList.begin(), itemList.end(), item);
	itemList.erase(it);
}


