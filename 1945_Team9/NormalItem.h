#pragma once
#include "Item.h"
class NormalItem : public Item
{
public:
	using Super = Item;
	NormalItem();
	~NormalItem();

	virtual void Init(FPOINT pos, FPOINT size) override;
	virtual void Update() override;
	virtual void Release() override;
	virtual void Render(HDC hdc) override;
};

