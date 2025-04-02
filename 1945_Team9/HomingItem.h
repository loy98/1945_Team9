#pragma once
#include "Item.h"
class HomingItem : public Item
{
public:
	using Super = Item;
	HomingItem();
	~HomingItem();

	virtual void Init(FPOINT pos, FPOINT size) override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;
};
