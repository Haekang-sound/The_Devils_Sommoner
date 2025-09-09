#pragma once
#include "Component.h"

class GameObject;

class Item : public Component
{
public:
	Item();
	virtual ~Item();

public:
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;
	
public:
	//virtual void Select(GameObject* player) abstract;
	virtual void Select() abstract;
	virtual void UnSelect() abstract;
	virtual void Act(GameObject* player) abstract;

private:
	// �޽� ���� ������ ���� �־ �� �� ����.s ���� ��� ��?
};