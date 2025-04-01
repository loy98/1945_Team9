#pragma once
#include "Item.h"
class StraightItem : public Item
{
public:
	using Super = Item;
	StraightItem();
	~StraightItem();

	virtual void Init(FPOINT pos, FPOINT size) override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;
};

