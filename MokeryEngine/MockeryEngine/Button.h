#pragma once
#include "Component.h"
#include "framework.h"
#include <functional>

enum class ButtonState
{
	Normal,		// 기본
	Pressed,	// 눌림
	Hover,		// 마우스가 위에 있음
	Selected,	// 선택됨
	Disabled	// 상호 작용 x
};

class Button : public Component
{
public:
	virtual ~Button() {};
	// Component을(를) 통해 상속됨
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

public:
	// 클릭 했을 때 실행할 내용 (미리 람다로 등록해둔 내용 실행)
	void OnClick();
	void OnPressed();	// 눌리는 중
	void OnHover();
	void OnNormal();

	ButtonState GetButtonState() { return m_buttonState; }

	// 버튼의 사용여부를 정해줘!
	void SetDisabled() { m_buttonState = ButtonState::Disabled; }
	void SetEnable() { m_buttonState = ButtonState::Normal; }

	void SetOnClick(std::function<void(void)> onClick);
	void SetOnPressed(std::function<void(void)> onPress);
	void SetOnHover(std::function<void(void)> onHover);
	void SetOnNormal(std::function<void(void)> onNormal);


private:
	std::function<void(void)> m_onClick = []() {};	// 람다를 이용해서 기본값을 넣어주자
	std::function<void(void)> m_onPress = []() {};
	std::function<void(void)> m_onHover = []() {};
	std::function<void(void)> m_onNormal = []() {};

	// 사용해야 될 때가 오면 Get, Set 만들어주기
	ButtonState m_buttonState;
};

