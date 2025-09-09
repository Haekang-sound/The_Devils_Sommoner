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
	// �⺻ �̾��ٸ�
	if (m_buttonState != ButtonState::Disabled)
	{
		// ���ǿ� ���� ��ư ���¸� �����Ѵ�.
		/// ��ư���� �ִ°�
		if (collider.x < x && x < collider.z &&
			collider.y < y && y < collider.w)
		{
			// ��Ŭ��
			if (InputManager::GetInstance()->m_Mouse.IsButtonHold(InputManager::GetInstance()->m_Mouse.leftButton))
			{
				// ��ư ���� �ۿ��� �����鼭 ������ �� pressed �Լ��� �۵��ϴ� ���� ����
				if (m_buttonState == ButtonState::Pressed)
				{
					m_buttonState = ButtonState::Pressed;
					OnPressed();
				}		
			}

			// ���콺�� ��ư ���� �����鼭 �⺻������ ��� 
			if (m_buttonState == ButtonState::Normal)
			{
				// ���¸� ȣ�������� �ٲ��ش�.
				m_buttonState = ButtonState::Hover;
				OnHover();
			}

			if (m_buttonState == ButtonState::Hover)
			{
				OnHover();
			}

			// ���콺�� Ŭ�� �ϸ� -> onPress�� ���� �����Ѵ�.
			if (InputManager::GetInstance()->m_Mouse.IsButtonDown(InputManager::GetInstance()->m_Mouse.leftButton))
			{
				m_buttonState = ButtonState::Pressed;
				OnPressed();
			}
			// ���� ���°� getkey down �Ǵ� getkey �϶�
			if (InputManager::GetInstance()->m_Mouse.IsButtonUp(InputManager::GetInstance()->m_Mouse.leftButton))
			{
				if (m_buttonState == ButtonState::Pressed)
				{
					m_buttonState = ButtonState::Selected;
					OnClick();
					m_buttonState = ButtonState::Hover;	// �̰� ��Ȳ�� ���� �ٲ� �� �ִ�
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

// OnClick �Լ��� �����Ѵ�.
void Button::SetOnClick(std::function<void(void)> onClick)
{
	m_onClick = onClick;
}

// OnPressed�Լ��� �����Ѵ�.
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


