#pragma once
#include "Component.h"
#include "framework.h"
#include <functional>

enum class ButtonState
{
	Normal,		// �⺻
	Pressed,	// ����
	Hover,		// ���콺�� ���� ����
	Selected,	// ���õ�
	Disabled	// ��ȣ �ۿ� x
};

class Button : public Component
{
public:
	virtual ~Button() {};
	// Component��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

public:
	// Ŭ�� ���� �� ������ ���� (�̸� ���ٷ� ����ص� ���� ����)
	void OnClick();
	void OnPressed();	// ������ ��
	void OnHover();
	void OnNormal();

	ButtonState GetButtonState() { return m_buttonState; }

	// ��ư�� ��뿩�θ� ������!
	void SetDisabled() { m_buttonState = ButtonState::Disabled; }
	void SetEnable() { m_buttonState = ButtonState::Normal; }

	void SetOnClick(std::function<void(void)> onClick);
	void SetOnPressed(std::function<void(void)> onPress);
	void SetOnHover(std::function<void(void)> onHover);
	void SetOnNormal(std::function<void(void)> onNormal);


private:
	std::function<void(void)> m_onClick = []() {};	// ���ٸ� �̿��ؼ� �⺻���� �־�����
	std::function<void(void)> m_onPress = []() {};
	std::function<void(void)> m_onHover = []() {};
	std::function<void(void)> m_onNormal = []() {};

	// ����ؾ� �� ���� ���� Get, Set ������ֱ�
	ButtonState m_buttonState;
};

