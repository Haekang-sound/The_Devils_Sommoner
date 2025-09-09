#pragma once
#include "Component.h"
#include "framework.h"

class PlayerComponent;
class SpriteRenderer;
class Transform;

// ����. ���׹̳��� ���� xũ�⸸ �ٲ�����
class StaminaUI : public Component
{
public:

	StaminaUI();
	virtual ~StaminaUI();

	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetRect(RECT _rect);

private:
	PlayerComponent* m_player;
	SpriteRenderer* m_sprite;
	Transform* m_transform;
	RECT m_rect;
};

