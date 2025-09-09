#pragma once
#include "InteractiveObject.h"

class GameObject;

class HeartChest : public InteractiveObject
{
	using Super = InteractiveObject;
public:
	HeartChest();
	virtual ~HeartChest();

	virtual void Start();
	virtual void Update(float dTime);
public:
	void InteractAddTime(float dTime) override;
	void Interact() override;

	void SetHeartChestModel(GameObject* model);
private:
	bool m_isDisabled;

private:
	GameObject* m_heartChestModel;
};

