#include "pch.h"
#include "Button.h"

#include "GameObject.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "SpriteRenderer.h"






void Button::Start()
{
	m_buttonState = ButtonState::Normal;
	OnNormal();
}

void Button::FixedUpdate(float dTime)
{
}

void Button::Update(float dTime)
{
	//std::cout << m_MousePosInfo.x << " " << m_MousePosInfo.y << std::endl;
	SimpleMath::Vector4 collider = m_pOwner->GetComponent<SpriteRenderer>()->GetNormalRect();
	float x, y;
	auto mouse = InputManager::GetInstance()->m_Mouse;
	x = mouse.m_NormalPosX;
	y = mouse.m_NormalPosY;
	// 기본 이었다면
	if (m_buttonState != ButtonState::Disabled)
	{
		// 조건에 따라 버튼 상태를 점검한다.
		/// 버튼위에 있는가
		if (collider.x < x && x < collider.z &&
			collider.y < y && y < collider.w)
		{
			// 좌클릭
			if (InputManager::GetInstance()->m_Mouse.IsButtonHold(InputManager::GetInstance()->m_Mouse.leftButton))
			{
				// 버튼 영역 밖에서 누르면서 들어왔을 때 pressed 함수가 작동하는 것을 막음
				if (m_buttonState == ButtonState::Pressed)
				{
					m_buttonState = ButtonState::Pressed;
					OnPressed();
				}		
			}

			// 마우스가 버튼 위에 있으면서 기본상태일 경우 
			if (m_buttonState == ButtonState::Normal)
			{
				// 상태를 호버링으로 바꿔준다.
				m_buttonState = ButtonState::Hover;
				OnHover();
			}

			if (m_buttonState == ButtonState::Hover)
			{
				OnHover();
			}

			// 마우스를 클릭 하면 -> onPress에 먼저 접근한다.
			if (InputManager::GetInstance()->m_Mouse.IsButtonDown(InputManager::GetInstance()->m_Mouse.leftButton))
			{
				m_buttonState = ButtonState::Pressed;
				OnPressed();
			}
			// 이전 상태가 getkey down 또는 getkey 일때
			if (InputManager::GetInstance()->m_Mouse.IsButtonUp(InputManager::GetInstance()->m_Mouse.leftButton))
			{
				if (m_buttonState == ButtonState::Pressed)
				{
					m_buttonState = ButtonState::Selected;
					OnClick();
					m_buttonState = ButtonState::Hover;	// 이건 상황에 따라 바뀔 수 있다
				}
			}
		}
		else
		{
			m_buttonState = ButtonState::Normal;
			OnNormal();
		}
	}

}

void Button::LateUpdate(float dTime)
{
}

void Button::Render()
{
}

void Button::Release()
{
}

void Button::OnClick()
{
	m_onClick();
	SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fClick);
}

void Button::OnPressed()
{
	m_onPress();

}

void Button::OnHover()
{
	m_onHover();
}

void Button::OnNormal()
{
	m_onNormal();
}

// OnClick 함수를 세팅한다.
void Button::SetOnClick(std::function<void(void)> onClick)
{
	m_onClick = onClick;
}

// OnPressed함수를 세팅한다.
void Button::SetOnPressed(std::function<void(void)> onPress)
{
	m_onPress = onPress;
}

void Button::SetOnHover(std::function<void(void)> onHover)
{
	m_onHover = onHover;
}

void Button::SetOnNormal(std::function<void(void)> onNormal)
{
	m_onNormal = onNormal;
}


