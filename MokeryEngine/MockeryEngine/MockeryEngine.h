#pragma once
#ifdef _DEBUG
	#pragma comment(lib, "../Libraries/DebugLib/KSL/KestrelSoundLibrary.lib")
	#pragma comment(lib, "../Libraries/DebugLib/Graphics/Graphics.lib")
#else

#endif

#include <Windows.h>



/// <summary>
/// 조롱엔진에 오신것을 
/// 조롱합니다.
/// </summary>

// 엔진 헤더에 d3d가 없어야 한다.
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
	
	// 초기화에 이 두가지를 같이 넣어주는게 좀 그렇다.
	void Initialize(HINSTANCE& hInst, HWND& hWnd);
	float Update();
	void Render();
	void Finalize(); 

	// get/set
public:
	ID3DRenderer* GetRenderer() const { return m_renderer; }
	void SetRenderer(ID3DRenderer* val) { m_renderer = val; }

	// 그래픽스 엔진 
private:
	ID3DRenderer* m_renderer;

	// 매니저
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

