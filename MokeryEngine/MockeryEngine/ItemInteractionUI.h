#pragma once
#include "Component.h"
#include "framework.h"

class InteractiveObject;
class SpriteRenderer;

/// <summary>
/// ItemBox를 열때 상호작용정도를 표시하는 UI
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
	RECT m_pos; // ui라면 자기 위치는 알아야지
	//SpriteRenderer* m_sprite;

	std::vector<InteractiveObject*> m_interacts;
	InteractiveObject* m_currentInteract;

};

