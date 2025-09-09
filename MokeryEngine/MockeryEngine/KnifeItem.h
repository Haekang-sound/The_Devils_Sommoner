#pragma once
#include "Item.h"

class GameObject;

class KnifeItem : public Item
{
public:
	KnifeItem();
	virtual ~KnifeItem();


public:
	void Start() override;
	void Select() override;
	void UnSelect() override;
	void Act(GameObject* player) override;


public:
	void SetKnifeObject(GameObject* knife);
	void SetHandModel(GameObject* obj);

private:
	GameObject* m_knifeObject;
	GameObject* m_handModel;
};

