#pragma once
#include "config.h"
#include "Singleton.h"

class Item;
class ItemManager : public Singleton<ItemManager>
{
public:
	ItemManager();
	~ItemManager();

	void Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	void AddItem(ItemType type, FPOINT pos, FPOINT size);
	void DeleteItem(Item* item);

	//Item* CreateItem(FPOINT pos);

private:
	vector<Item*> itemList;
};

