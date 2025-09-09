#include "pch.h"
#include "framework.h"
#include "../MockeryEngine/InputManager.h"
#include "GameProcess.h"

#pragma comment (lib,"DirectXTex.lib")
#ifdef _DEBUG
#pragma comment(lib, "assimp-vc143-mtd.lib")

#else
#pragma comment(lib, "assimp-vc143-mt.lib")
#endif



GameProcess::GameProcess()
	:m_hInst(nullptr), m_hWnd(nullptr), m_msg{}, m_wcex{},
	m_windowHeight(1080), m_windowWidth(1920),

	m_renderer(nullptr), m_MEngine(nullptr)
{

}

GameProcess::~GameProcess()
{
}

void GameProcess::Initialize(HINSTANCE hInst)
{
	m_hInst = hInst;

	// �������� �ʱ�ȭ�� �����Ѵ�.
	WinInit();

	// �������� �����Ѵ�.
	m_renderer = ID3DRenderer::CreateRenderer();
	m_renderer->Init((int)m_hInst, (int)m_hWnd, 1080, 1920,0.3334);

	// ������ �����Ѵ�.
	m_MEngine = new MockeryEngine();
	m_MEngine->SetRenderer(m_renderer);
	m_MEngine->Initialize(m_hInst, m_hWnd);

}

void GameProcess::Loop()
{
	while (m_msg.message != WM_QUIT)
	{
		if (PeekMessage(&m_msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		else
		{
			Update();
			Render();

		}
	}
}

void GameProcess::Finalize()
{
	m_renderer->Finalize();
	delete m_renderer;

	m_MEngine->Finalize();
	delete m_MEngine;
}

void GameProcess::Update()
{
	float dTime = m_MEngine->Update();
	m_renderer->Update(dTime);
}

void GameProcess::Render()
{
	m_renderer->BeginRender();
	m_MEngine->Render();
	m_renderer->EndRender();
}


void GameProcess::WinInit()
{
	// 1. ������ Ŭ�������
	MyRegisterClass(m_hInst);
	// �޴� ����
	// 2. ũ������Ʈ ������ (hWnd������)
	
	// �޴��ٸ� ����ϴ�.
	// SetMenu(m_hWnd, NULL);

	m_hWnd = CreateWindowW(
		L"MockeryEngine",		// lpClassName
		L"Ȳ������",				// lpWindowName
		WS_POPUP,	// dwStyle // WS_POPUP
		0,			// â�� �ʱ� ���� ��ġ
		0,						// â�� �ʱ� ���� ��ġ
		m_windowWidth,					// â�� �ʺ�(����̽� ����)�Դϴ�.
		m_windowHeight,					// â�� ����(����̽� ����)�Դϴ�
		nullptr, nullptr, m_hInst, nullptr);

	//SetMenu(m_hWnd, NULL);

	if (!m_hWnd)
	{
		return;
	}

	// 3. show, update window
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

}

LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
#pragma region Mouse

	case WM_ACTIVATE:
	case WM_ACTIVATEAPP:
		InputManager::GetInstance()->m_pKeyboardData->ProcessMessage(message, wParam, lParam);
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		InputManager::GetInstance()->m_pMouseData->ProcessMessage(message, wParam, lParam);
		break;

#pragma endregion
#pragma region Keyboard


	case WM_SYSKEYDOWN:
		if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
		{
			// This is where you'd implement the classic ALT+ENTER hotkey for fullscreen toggle
		}
		InputManager::GetInstance()->m_pKeyboardData->ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:
	 		if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
 			PostQuitMessage(0);
	case WM_KEYUP:
	case WM_SYSKEYUP:
		InputManager::GetInstance()->m_pKeyboardData->ProcessMessage(message, wParam, lParam);
		break;

#pragma endregion
// 	case WM_KEYDOWN:
// 		// esc�� ������ ����
// 		if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
// 			PostQuitMessage(0);
// 		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM GameProcess::MyRegisterClass(HINSTANCE hInstance)
{
	m_wcex.cbSize = sizeof(WNDCLASSEX);

	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc = GameProcess::WndProc;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;
	m_wcex.hInstance = hInstance;
	m_wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wcex.lpszMenuName = NULL;
	m_wcex.lpszClassName = L"MockeryEngine";

	return RegisterClassExW(&m_wcex);
}


