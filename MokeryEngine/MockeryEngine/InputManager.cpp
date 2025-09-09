#include "pch.h"
#include "InputManager.h"


void InputManager::Init(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_pMouseData = std::make_unique<DirectX::Mouse>();
	m_pMouseData.get()->SetWindow(_hWnd);
	m_pKeyboardData = std::make_unique<DirectX::Keyboard>();
	m_Mouse.m_hWnd = _hWnd;
}

void InputManager::Finalize()
{

}

void InputManager::Update()
{
	// 비효율적인 코드.. 일단 사용함.
	//GetWindowRect(m_hWnd, &m_Mouse.windowRect);
	static bool relativeCheck = m_IsMouseRelative;

	if (m_hWnd == GetForegroundWindow())
	{
		RECT clientRect{};
		GetClientRect(m_hWnd, &clientRect);

		static int width{}, height{};
		width = clientRect.right - 1;
		height = clientRect.bottom - 1;

		POINT clientPoint{};
		ClientToScreen(m_hWnd, &clientPoint);

		clientRect.top += clientPoint.y;
		clientRect.bottom += clientPoint.y;
		clientRect.left += clientPoint.x;
		clientRect.right += clientPoint.x;

		ClipCursor(&clientRect);

		m_Keyboard.Update(m_pKeyboardData.get()->GetState());
		m_Mouse.Update(m_pMouseData.get()->GetState());
		if (relativeCheck != m_IsMouseRelative)
		{
			if (m_IsMouseRelative == true)
			{
				m_pMouseData.get()->SetMode(DirectX::Mouse::MODE_RELATIVE);
			}
			else
			{
				m_pMouseData.get()->SetMode(DirectX::Mouse::MODE_ABSOLUTE);
			}
			relativeCheck = m_IsMouseRelative;
		}
		m_Mouse.MouseMove(m_IsMouseRelative);
	}
	else
	{
		ClipCursor(nullptr);
	}

}

void InputManager::SetMouseMode(bool _IsRelative)
{
	m_IsMouseRelative = _IsRelative;
	
}


bool __cdecl InputManager::Keyboard::IsKeyHold(char _key) const noexcept
{
	return lastState.IsKeyDown((DirectX::Keyboard::Keys)_key);
}

bool __cdecl InputManager::Keyboard::IsKeydown(char _key) const noexcept
{

	return IsKeyPressed((DirectX::Keyboard::Keys)_key);
}

bool __cdecl InputManager::Keyboard::IsKeyUp(char _key) const noexcept
{

	return IsKeyReleased((DirectX::Keyboard::Keys)_key);
}

bool __cdecl InputManager::Mouse::IsButtonDown(ButtonState _bs) const noexcept
{
	return (_bs == PRESSED);
}

bool __cdecl InputManager::Mouse::IsButtonHold(ButtonState _bs) const noexcept
{
	return (_bs == HELD);
}

bool __cdecl InputManager::Mouse::IsButtonUp(ButtonState _bs) const noexcept
{
	return (_bs == RELEASED);
}

bool __cdecl InputManager::Mouse::IsButtonHover(ButtonState _bs) const noexcept
{
	return (_bs == UP);
}

void InputManager::Mouse::MouseMove(bool _IsRelative)
{
	// 마우스 위치를 가져온다.5
	

	m_Curr = GetLastState();

	{
		m_PosX = m_Curr.x;
		m_PosY = m_Curr.y;
		if (_IsRelative == false)
		{
			RECT rc;
			GetClientRect(m_hWnd,&rc);

			m_NormalPosX = m_PosX / rc.right;
			m_NormalPosY = m_PosY / rc.bottom;

		}
		
		
	}



}