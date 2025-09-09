#pragma once
#include "SingleTon.h"
#include "framework.h"
#include "../Libraries/DXTK/Inc/Keyboard.h"
#include "../Libraries/DXTK/Inc/Mouse.h"



class InputManager : public SingleTon<InputManager>
{
public:
	void Init(HWND _hWnd);
	void Finalize();
	void Update();

private:
	class Keyboard : public DirectX::Keyboard::KeyboardStateTracker
	{
	public:
		bool __cdecl IsKeyHold(char _key) const noexcept;

		bool __cdecl IsKeydown(char _key) const noexcept;
		bool __cdecl IsKeyUp(char _key) const noexcept;
	};

	class Mouse : public DirectX::Mouse::ButtonStateTracker
	{
	public:

		bool __cdecl IsButtonDown(ButtonState _bs) const noexcept;

		bool __cdecl IsButtonHold(ButtonState _bs) const noexcept;

		bool __cdecl IsButtonUp(ButtonState _bs) const noexcept;

		bool __cdecl IsButtonHover(ButtonState _bs) const noexcept;

		void MouseMove();

		bool isMove = false;
		int moveX = 0;
		int moveY = 0;

		DirectX::Mouse::State prev;
		bool isMouseCenter = false;
	};

public:
	Keyboard m_Keyboard;
	Mouse m_Mouse;
	// DirectX::Keyboard::KeyboardStateTracker m_Keyboard;
	RECT windowRect;
	RECT clientRect;

private:
	HWND m_hWnd;


private:

	friend class GameProcess;
	std::unique_ptr<DirectX::Keyboard> m_pKeyboardData;
	std::unique_ptr<DirectX::Mouse> m_pMouseData;

};

// 
// enum class KeyType
// {
// 	LeftMouse = VK_LBUTTON,
// 	RightMouse = VK_RBUTTON,
// 
// 	Up = VK_UP,
// 	Down = VK_DOWN,
// 	Left = VK_LEFT,
// 	Right = VK_RIGHT,
// 	SpaceBar = VK_SPACE,
// 
// 	W = 'W',
// 	A = 'A',
// 	S = 'S',
// 	D = 'D',
// 
// 	Q = 'Q',
// 	E = 'E',
// 
// 	Esc = VK_ESCAPE
// };
// 
// enum class KeyState
// {
// 	None,
// 	Press,
// 	Down,
// 	Up,
// 
// 	End
// };
// 
// enum
// {
// 	KEY_TYPE_COUNT = static_cast<__int32>(UINT8_MAX) + 1,
// 	KEY_STATE_COUNT = static_cast<__int32>(KeyState::End)
// };
// 
// class InputManager
// {
// public:
// 	InputManager();
// 	~InputManager();
// 
// public:
// 	void Init(HWND hwnd);
// 	void Update();
// 
// 	// 누르고 있을 때
// 	bool GetButton(KeyType key ) { return GetState(key) == KeyState::Press; }
// 
// 	// 맨 처음 눌렀을 때
// 	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down; }
// 
// 	// 맨 처음 눌렀다가 땔 때
// 	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up; }
// 
// 	POINT GetMousePos() { return m_mousePos; }
// 
// private:
// 	KeyState GetState(KeyType key) 
// 	{
// 		return  m_states[static_cast<unsigned __int8>(key)]; 
// 	}
// 
// private:
// 	HWND m_hwnd = 0;
// 	std::vector<KeyState> m_states;
// 	POINT m_mousePos;
// };

