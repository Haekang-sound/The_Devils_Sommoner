#pragma once
#include "Component.h"

class Item;

class Inventory : public Component
{
public:
	Inventory();
	virtual ~Inventory();

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	void AddItem(Item* item);
	Item* SelectItem(int index);

private:
	std::vector<Item*> m_items;
};

