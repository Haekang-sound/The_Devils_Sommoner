#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "../Libraries/DebugLib/MockeryEngine/MockeryEngine.lib")

	#include <iostream>
#else

#endif

#include "../MockeryEngine/MockeryEngine.h"
#include "../Graphics/ID3DRenderer.h"


class MockeryEngine;

class GameProcess 
{
public:
	GameProcess();
	~GameProcess();

	void	Initialize(HINSTANCE hInst);
	void	Loop();			
	void	Finalize();		

private:
	void	Update();
	void	Render();

/// 윈도우즈 초기화 내용
private:
	void	WinInit();
	static	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	ATOM	MyRegisterClass(HINSTANCE hInstance);

	HINSTANCE m_hInst;
	HWND m_hWnd;
	WNDCLASSEXW m_wcex;
	MSG m_msg;
	
	int m_windowHeight;
	int m_windowWidth;

private:
	MockeryEngine* m_MEngine;
	ID3DRenderer* m_renderer;
};

