#pragma once
#include "Component.h"
#include "framework.h"

class InteractiveObject;
class SpriteRenderer;

/// <summary>
/// ItemBox�� ���� ��ȣ�ۿ������� ǥ���ϴ� UI
/// 
/// </summary>
class ItemInteractionUI : public Component
{
public:
	ItemInteractionUI();
	virtual ~ItemInteractionUI();

	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetUIRect(RECT _rect) { m_pos = _rect; };


private:
	RECT m_pos; // ui��� �ڱ� ��ġ�� �˾ƾ���
	//SpriteRenderer* m_sprite;

	std::vector<InteractiveObject*> m_interacts;
	InteractiveObject* m_currentInteract;

};

