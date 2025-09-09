#pragma once
#include "Component.h"
#include "framework.h"

class ItemChest;
class SpriteRenderer;
class Button;


/// <summary>
/// Item이 사용되었을때 
/// Item 설명을 띄워주는 UI
/// 오해강
/// </summary>
class ItemDescUI : public Component
{
public:
	ItemDescUI();
	virtual ~ItemDescUI();
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	RECT m_pos;
	bool m_isPresent = false;
	float m_presentTime;
	bool m_forSound = false;

private:
	std::vector<ItemChest*> m_itemChests;
	SpriteRenderer* m_sprite;
	
	Button* m_button;
};

