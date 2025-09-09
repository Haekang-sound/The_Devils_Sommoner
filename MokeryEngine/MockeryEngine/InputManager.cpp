#include "pch.h"
#include "InputManager.h"
#ifdef _DEBUG
#include <iostream>
#endif


void InputManager::Init(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_pMouseData = std::make_unique<DirectX::Mouse>();
	m_pKeyboardData = std::make_unique<DirectX::Keyboard>();
}

void InputManager::Finalize()
{

}

void InputManager::Update()
{
	GetWindowRect(m_hWnd, &windowRect);
	GetClientRect(m_hWnd, &clientRect);
	m_Keyboard.Update(m_pKeyboardData.get()->GetState());
	m_Mouse.Update(m_pMouseData.get()->GetState());
	m_Mouse.MouseMove();

	std::cout << "(" << m_Mouse.GetLastState().x<< ", " << m_Mouse.GetLastState().y<< ')' << std::endl;

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

void InputManager::Mouse::MouseMove()
{
	isMove = false;
	static int x, y;

	// ���콺 ��ġ�� �����´�.
	x = GetLastState().x;
	y = GetLastState().y;



	// ���� ���� �⺻���� �ٸ���
	// ���� x�� y�� ������ġ�� �ٸ��ٸ�
	if (isMouseCenter == false)
	{
		if ((x != prev.x) || (y != prev.y))
		{
			// move ���� ��ȭ���� �Է��ϰ�.
			moveX = x - prev.x;
			moveY = y - prev.y;

			// ���콺 �̵��� true�� �ٲ۴�.
			isMove = true;
		}
	}
	else
	{
		moveX = 0;
		moveY = 0;
		isMouseCenter = false;
	}

	prev = GetLastState();
}


// InputManager::InputManager()
// 	:m_mousePos{}
// {
// 
// }
// 
// InputManager::~InputManager()
// {
// 
// }
// 
// void InputManager::Init(HWND hwnd)
// {
// 	m_hwnd = hwnd;
// 	m_states.resize(KEY_TYPE_COUNT, KeyState::None);
// }
// 
// void InputManager::Update()
// {
// 	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
// 	if (::GetKeyboardState(asciiKeys) == false)
// 		return;
// 
// 	for (int key = 0; key < KEY_TYPE_COUNT; key++)
// 	{
// 		// Ű�� ���� ������ true
// 		if (asciiKeys[key] & 0x80)
// 		{
// 			KeyState& state = m_states[key];
// 
// 			// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
// 			if (state == KeyState::Press || state == KeyState::Down)
// 				state = KeyState::Press;
// 			else
// 				state = KeyState::Down;
// 		}
// 		else
// 		{
// 			KeyState& state = m_states[key];
// 
// 			// ���� �����ӿ� Ű�� ���� ���¶�� UP
// 			if (state == KeyState::Press || state == KeyState::Down)
// 				state = KeyState::Up;
// 			else
// 				state = KeyState::None;
// 		}
// 	}
// 
// 	// Mouse
//  	::GetCursorPos(&m_mousePos); // Ŀ���� ��ǥ�� �˾ƿ´�
// 	::ScreenToClient(m_hwnd, &m_mousePos);
// }