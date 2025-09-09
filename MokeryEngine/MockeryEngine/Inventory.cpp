#include "pch.h"
#include "Inventory.h"

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

void Inventory::Start()
{

}

void Inventory::FixedUpdate(float dTime)
{

}

void Inventory::Update(float dTime)
{

}

void Inventory::LateUpdate(float dTime)
{

}

void Inventory::Render()
{

}

void Inventory::Release()
{
	m_items.clear();
}

void Inventory::AddItem(Item* item)
{
	m_items.push_back(item);
}

Item* Inventory::SelectItem(int index)
{
	if (index < m_items.size())
	{
		return m_items[index];
	}
	return nullptr;
}
