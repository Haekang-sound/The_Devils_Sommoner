#pragma once
#ifdef _DEBUG
	#pragma comment(lib, "../Libraries/DebugLib/KSL/KestrelSoundLibrary.lib")
	#pragma comment(lib, "../Libraries/DebugLib/Graphics/Graphics.lib")
#else

#endif

#include <Windows.h>



/// <summary>
/// ���տ����� ���Ű��� 
/// �����մϴ�.
/// </summary>

// ���� ����� d3d�� ����� �Ѵ�.
class ID3DRenderer;
class TimeManager;
class InputManager;
class SceneManager;

//class Scene;

class MockeryEngine
{
public:
	MockeryEngine();
	~MockeryEngine();
	
	// �ʱ�ȭ�� �� �ΰ����� ���� �־��ִ°� �� �׷���.
	void Initialize(HINSTANCE& hInst, HWND& hWnd);
	float Update();
	void Render();
	void Finalize(); 

	// get/set
public:
	ID3DRenderer* GetRenderer() const { return m_renderer; }
	void SetRenderer(ID3DRenderer* val) { m_renderer = val; }

	// �׷��Ƚ� ���� 
private:
	ID3DRenderer* m_renderer;

	// �Ŵ���
private:
	TimeManager* m_timeManager;
	SceneManager* m_sceneManager;
	//InputManager* m_inputManager;

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	float fixTime;
	float fixRenderTime;
	const float fixNow;
	const float fixRenderNow;

	float dTime;

};

