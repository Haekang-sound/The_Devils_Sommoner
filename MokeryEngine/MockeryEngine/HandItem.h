#pragma once
#include "Item.h"
class HandItem : public Item
{
public:
	HandItem();
	virtual ~HandItem();

public:
	void Start() override;
	void Select() override;
	void UnSelect() override;
	void Act(GameObject* player) override;

public:
	void SetHandModel(GameObject* obj);

private:
	GameObject* m_handModel;
};

