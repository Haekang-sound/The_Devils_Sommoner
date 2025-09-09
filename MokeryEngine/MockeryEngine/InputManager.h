#pragma once
#include "SingleTon.h"
#include "framework.h"
#include "../Libraries/DXTK/Inc/Keyboard.h"
#include "../Libraries/DXTK/Inc/Mouse.h"

#define _DX

#ifdef _DX
#define DX(x) x
#else
#define DX(x)
#endif // 



class InputManager : public SingleTon<InputManager>
{
public:
	void Init(HWND _hWnd);
	void Finalize();
	void Update();

public:
	void SetMouseMode(bool _IsRalative);

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
		friend class InputManager;
	public:

		bool __cdecl IsButtonDown(ButtonState _bs) const noexcept;

		bool __cdecl IsButtonHold(ButtonState _bs) const noexcept;

		bool __cdecl IsButtonUp(ButtonState _bs) const noexcept;

		bool __cdecl IsButtonHover(ButtonState _bs) const noexcept;
	private:
		
		void MouseMove(bool _IsRelative);

	public:
		float m_PosX, m_PosY;
		float m_NormalPosX, m_NormalPosY;

	private:
		

		DirectX::Mouse::State m_Curr;
		DirectX::Mouse::State m_Prev;

		HWND m_hWnd;
	};

public:
	Keyboard m_Keyboard;
	Mouse m_Mouse;



private:
	HWND m_hWnd;
	bool m_IsMouseRelative;

private:

	friend class GameProcess;
	std::unique_ptr<DirectX::Keyboard> m_pKeyboardData;
	std::unique_ptr<DirectX::Mouse> m_pMouseData;

};