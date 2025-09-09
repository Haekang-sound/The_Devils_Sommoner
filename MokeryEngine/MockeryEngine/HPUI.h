#pragma once
#include "Component.h"
#include "framework.h"

// �ϴ�.. �ش��ϴ� ���³ѹ��� �ϵ��ڵ����� �Ѱ��ִ� ����� �ִ�.
enum HPUIState
{
	None = 0,
	Half,
	Fatal
};

class PlayerComponent;
class SpriteRenderer;
class Button;

class HPUI : public Component
{
public:
	HPUI();
	virtual ~HPUI() {};
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetUIRect(RECT _rect) { m_pos = _rect; };

private:
	RECT m_pos;
	bool m_isDead;

private:
	PlayerComponent* m_player;
	//SpriteRenderer* m_sprite;

	// ����� Ȯ�ο�
	Button* m_button;
};

