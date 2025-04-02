#pragma once
#include "Item.h"
class LaserItem : public Item
{
public:
	using Super = Item;
	LaserItem();
	~LaserItem();

	virtual void Init(FPOINT pos, FPOINT size) override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;
};

