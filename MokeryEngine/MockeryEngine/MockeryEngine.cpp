#include "pch.h"
#include "MockeryEngine.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameManager.h"

#include "Component.h"


MockeryEngine::MockeryEngine()
	:m_hInst(nullptr), m_hWnd(nullptr),
	fixTime(NULL), fixNow(0.01f),
	fixRenderTime(NULL), fixRenderNow(0.01f),
	m_renderer(nullptr),
	m_timeManager(nullptr), m_sceneManager(nullptr)
{}

MockeryEngine::~MockeryEngine()
{}

void MockeryEngine::Initialize(HINSTANCE& hInst, HWND& hWnd)
{
	m_hInst = hInst;
	m_hWnd = hWnd;

#pragma region Init
	m_timeManager = new TimeManager();
	m_timeManager->Init();

	//m_inputManager = new InputManager();
	//m_inputManager->Init(m_hWnd);
	InputManager::GetInstance()->Init(hWnd);

	m_sceneManager = new SceneManager();
	m_sceneManager->SetRenderer(m_renderer);	// �������� �޾ƿ´�.
	Component::SetRenderer(m_renderer);
	m_sceneManager->Init(m_timeManager);//, m_inputManager);

#pragma endregion

}

float MockeryEngine::Update()
{
	m_timeManager->Update();
	dTime = m_timeManager->GetDTime();

	InputManager::GetInstance()->Update();
	GameManager::GetInstance()->Update();

	fixTime += dTime;
	if (fixTime > fixNow)
	{
		m_sceneManager->FixedUpdate(dTime);	// fixNow�ð��� �ɶ����� ����ȴ�.
		fixTime = 0.f;
	}
	m_sceneManager->Update(dTime);
	m_sceneManager->LateUpdate(dTime);

	return dTime;
}

// �������� �׷��Ƚ����� �������� ����ϱ�� �Ͽ���.
void MockeryEngine::Render()
{
	m_sceneManager->Render();
	m_renderer->Render();
}

void MockeryEngine::Finalize()
{
	m_sceneManager->Finalize();
	delete m_sceneManager;

	delete m_timeManager;


	InputManager::GetInstance()->Finalize();
	delete InputManager::GetInstance();

	GameManager::GetInstance()->Finalize();
	delete GameManager::GetInstance();
}
