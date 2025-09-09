#include "pch.h"

// 라이브러리
#pragma region Lib
#include "../KestrelSoundLibrary/KestrelSoundLibrary.h"
#pragma endregion Lib

// 매니저
#pragma region Manager
#include "SceneManager.h"
#include "InputManager.h"
#include "CollisionDetectManager.h"
#include "PhysicsManager.h"
#include "EngineResourceManager.h"
#include "EngineObjectManager.h"
#include "SoundManager.h"
#include "GameManager.h"
#pragma endregion Manager

// Scene
#pragma region Scene
#include "IntroScene.h"		// 
#include "TitleScene.h"		// 
#include "EndingScene.h"	// 
#pragma endregion Scene

SceneManager::SceneManager()
	: m_currentScene(nullptr), m_newScene(nullptr),
	m_sceneMap{},
	m_resourceManager(nullptr), m_objManager(nullptr), m_timeManager(nullptr), // m_inputManager(nullptr),
	m_renderer(nullptr)//,m_soundKSL(nullptr)
{

}

SceneManager::~SceneManager()
{
	
}

/// <summary>
/// 첫번째 scene을 생성하고 
/// 필요한 리소스들을 가져오자
/// </summary>
void SceneManager::Init(TimeManager* timeManager)//, InputManager* inputManager)
{
	// 매개변수를 세팅한다.
	m_timeManager = timeManager;
	//m_inputManager = inputManager;

	m_collisionDetectManager = new CollisionDetectManager();
	m_collisionDetectManager->Init();
	m_collisionDetectManager->SetRenderer(m_renderer);
	m_physicsManager = new PhysicsManager();
	m_physicsManager->Init();

	// 클래스에서 필요한 생성, 초기화를 진행한다
#pragma region construct

	// 사운드 매니저의 초기화
	SoundManager::GetInstance().Init();
	
	m_resourceManager = new EngineResourceManager();
	m_resourceManager->Init(SoundManager::GetInstance().getKSL());

	m_objManager = new EngineObjectManager();
	m_objManager->Init();

#pragma endregion

	LoadResource();
	// scene을 추가한다.
	AddScene(SceneNumber::Intro);
	AddScene(SceneNumber::Title);

	// 1. 초기 scene을 설정한다.
	SetCurrentScene(SceneNumber::Intro);

	// 2. 초기 scene의 대한 초기화를 진행한다.
	//m_currentScene->SetKSL(m_soundManager->getKSL());
	m_currentScene->SetRenderer(m_renderer);
	m_currentScene->EditScene(m_resourceManager, m_objManager, m_timeManager, m_collisionDetectManager, m_physicsManager);//, m_inputManager);
	m_currentScene->Awake();
	m_currentScene->Start();
	
}

void SceneManager::LoadResource()
{
 	m_renderer->LoadModel("..\\Resources\\FBX\\01.Map\\97.Ground\\Ground.fbx", static_cast<int>(EnumModel::Ground));
 	m_renderer->LoadModel("..\\Resources\\FBX\\01.Map\\98.Ceiling\\Ceiling.fbx", static_cast<int>(EnumModel::Ceiling));
 	m_renderer->LoadModel("..\\Resources\\FBX\\01.Map\\00.wall1\\NoPillarWall.fbx", static_cast<int>(EnumModel::Wall));
 	m_renderer->LoadModel("..\\Resources\\FBX\\01.Map\\01.PillarWall\\PillarWall.fbx", static_cast<int>(EnumModel::PillarWall));
 	m_renderer->LoadModel("..\\Resources\\FBX\\02.Object\\HeartBox\\Heartbox.fbx", static_cast<int>(EnumModel::HeartBox));
 	m_renderer->LoadModel("..\\Resources\\FBX\\02.Object\\ItemBox\\Itembox.fbx", static_cast<int>(EnumModel::ItemBox));
 	m_renderer->LoadModel("..\\Resources\\FBX\\01.Map\\02.Door_1\\Door_1.fbx", static_cast<int>(EnumModel::Door));
 	m_renderer->LoadModel("..\\Resources\\FBX\\01.Map\\03.DoorFrame_1\\DoorFrame_1.fbx", static_cast<int>(EnumModel::DoorFrame));
 
 	m_renderer->LoadModel("..\\Resources\\FBX\\01.Map\\04.DevilAltar\\DevilAltar.fbx", static_cast<int>(EnumModel::DevilAltar));
 	m_renderer->LoadModel("..\\Resources\\FBX\\03.Model\\Blind\\Blind.fbx", static_cast<int>(EnumModel::EnemyBlind));
 	m_renderer->LoadModel("..\\Resources\\FBX\\03.Model\\JaneD\\JaneD.fbx", static_cast<int>(EnumModel::EnemyJaneD));
 	m_renderer->LoadModel("..\\Resources\\FBX\\03.Model\\Chaser\\Chaser.fbx", static_cast<int>(EnumModel::EnemyChaser));
 	m_renderer->LoadModel("..\\Resources\\FBX\\03.Model\\Ghost\\Ghost.fbx", static_cast<int>(EnumModel::EnemyGhost));
 	m_renderer->LoadModel("..\\Resources\\FBX\\02.Object\\Knife\\Knife.fbx", static_cast<int>(EnumModel::Knife));
 	m_renderer->LoadModel("..\\Resources\\FBX\\02.Object\\Heart\\Heart.fbx", static_cast<int>(EnumModel::Heart));
 	m_renderer->LoadModel("..\\Resources\\FBX\\02.Object\\Righthand\\Righthand.fbx", static_cast<int>(EnumModel::RightHand));
 	m_renderer->LoadModel("..\\Resources\\FBX\\02.Object\\Lefthand\\Lefthand.fbx", static_cast<int>(EnumModel::LeftHand));
 	m_renderer->LoadModel("..\\Resources\\FBX\\02.Object\\Righthand_knife\\righthand_knife.fbx", static_cast<int>(EnumModel::RightHandKnife));
 	m_renderer->LoadModel("..\\Resources\\FBX\\02.Object\\HeartSign\\HeartSign.fbx", static_cast<int>(EnumModel::HeartSign));
//  	//m_renderer->LoadModel("..\\Resources\\FBX\\02.Object\\Righthand_knife\\righthand_knife.fbx", static_cast<int>(EnumModel::RightHandKnife));
 	
	/// UI리소스
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Intro_BackGround));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Ending_BackGround));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Help_BackGround));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::GameStart_Button));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Help_Button));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Closs_Button));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::After_Button));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Before_Button));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Exit_Button));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::CrossHair_Icon));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Knife_Icon));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Symbol_Icon));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::ItemDesc_Icon));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Stamina));
	m_renderer->LoadSprite(static_cast<int>(EnumModel::Timer));



	m_renderer->AddTextureToSprite("..\\Resources\\UI\\MainBackGround\\Main_Title.png", static_cast<int>(EnumModel::Intro_BackGround), 0);

	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Ending\\Ending_Clear.png", static_cast<int>(EnumModel::Ending_BackGround), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Ending\\Ending_Dead.png", static_cast<int>(EnumModel::Ending_BackGround), 1);
									
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Help\\Help_1.png", static_cast<int>(EnumModel::Help_BackGround), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Help\\Help_2.png", static_cast<int>(EnumModel::Help_BackGround), 1);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Help\\Help_3.png", static_cast<int>(EnumModel::Help_BackGround), 2);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Help\\Help_4.png", static_cast<int>(EnumModel::Help_BackGround), 3);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Help\\Help_5.png", static_cast<int>(EnumModel::Help_BackGround), 4);
									
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\GameStart_off.png", static_cast<int>(EnumModel::GameStart_Button), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\GameStart_on.png", static_cast<int>(EnumModel::GameStart_Button), 1);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\Help_off.png", static_cast<int>(EnumModel::Help_Button), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\Help_on.png", static_cast<int>(EnumModel::Help_Button), 1);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\Closs_off.png", static_cast<int>(EnumModel::Closs_Button), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\Closs_on.png", static_cast<int>(EnumModel::Closs_Button), 1);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\After_off.png", static_cast<int>(EnumModel::After_Button), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\After_on.png", static_cast<int>(EnumModel::After_Button), 1);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\before_off.png", static_cast<int>(EnumModel::Before_Button), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\before_on.png", static_cast<int>(EnumModel::Before_Button), 1);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\Exit_off.png", static_cast<int>(EnumModel::Exit_Button), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Button\\Exit_on.png", static_cast<int>(EnumModel::Exit_Button), 1);
									
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\CrossHair\\crosshair.png", static_cast<int>(EnumModel::CrossHair_Icon), 0);
									
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Icon\\knife_on.png", static_cast<int>(EnumModel::Knife_Icon), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Icon\\knife_off.png", static_cast<int>(EnumModel::Knife_Icon), 1);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Icon\\Symbol.png", static_cast<int>(EnumModel::Symbol_Icon), 0);
									
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\ItemBox\\Hp_item_UI.png", static_cast<int>(EnumModel::ItemDesc_Icon), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\ItemBox\\devil_item_UI.png", static_cast<int>(EnumModel::ItemDesc_Icon), 1);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\ItemBox\\spdbuff_item_UI.png", static_cast<int>(EnumModel::ItemDesc_Icon), 2);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\ItemBox\\spdDebuff_item_UI.png", static_cast<int>(EnumModel::ItemDesc_Icon), 3);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\ItemBox\\timer_item_UI.png", static_cast<int>(EnumModel::ItemDesc_Icon), 4);

	// 스테미나 필요할지도 모르니까 일단 가져옴
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\StaminaBar\\StaminaBar.png", static_cast<int>(EnumModel::Stamina), 0);
	
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Timer\\timer_30sec.png", static_cast<int>(EnumModel::Timer), 0);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Timer\\timer_1min.png", static_cast<int>(EnumModel::Timer), 1);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Timer\\timer_2min.png", static_cast<int>(EnumModel::Timer), 2);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Timer\\timer_3min.png", static_cast<int>(EnumModel::Timer), 3);
	m_renderer->AddTextureToSprite("..\\Resources\\UI\\Timer\\timer_4min.png", static_cast<int>(EnumModel::Timer), 4);

}

void SceneManager::FixedUpdate(float dTime)
{
	m_currentScene->FixedUpdate(dTime);
	m_renderer->FixedUpdate();
}

/// <summary>                           
/// scene의 대한 업데이트가 이루어진다.
/// </summary>
void SceneManager::Update(float dTime)
{
	if (InputManager::GetInstance()->m_Keyboard.IsKeydown('P'))
	{
		ChangeScene(SceneNumber::Intro);
	}
	if (InputManager::GetInstance()->m_Keyboard.IsKeydown('O'))
	{
		ChangeScene(SceneNumber::Title);
	}
  	m_currentScene->Update(dTime);

	// 사운드 라이브러리의 대한 업데이트가 필요함
	SoundManager::GetInstance().Update();
}

void SceneManager::LateUpdate(float dTime)
{
	m_currentScene->LateUpdate(dTime);
	m_collisionDetectManager->Update();
	m_physicsManager->Update();
}

void SceneManager::Render()
{
	m_currentScene->Render();
}

void SceneManager::Finalize()
{
	
	m_currentScene->End();

	for (auto& e : m_sceneMap)
 	{
 		//e.second->End();
 		delete e.second;
		e.second = nullptr;
 	}
	m_sceneMap.clear();

	m_collisionDetectManager->Finalize();
	delete m_collisionDetectManager;

	m_physicsManager->Finalize();
	delete m_physicsManager;

	SoundManager::GetInstance().Finalize();

	m_resourceManager->Release();
	delete m_resourceManager;

	delete m_objManager;
}

/// <summary>
/// scene의 이름을 입력받고 새로운 scene을 생성, 보관한다.
/// -> init 할때 한 번에 해주면 개꿀일듯
/// </summary>
/// <param name="sceneName">scene 이름</param>
void SceneManager::AddScene(SceneNumber sceneName)
{
	switch (sceneName)
	{
	case SceneNumber::Title:
		m_newScene = new TitleScene();
		break;

	case SceneNumber::Intro:
		m_newScene = new IntroScene();
		break;
	}
	m_sceneMap.emplace(m_newScene->GetSceneNum(), m_newScene);
	m_newScene->SetSceneManger(this);		// sceneManager를 세팅한다
	m_newScene = nullptr;
}

/// <summary>
/// 여기서 필요한 리소스들을 가져오자
/// </summary>
/// <param name="seceneName"></param>
void SceneManager::ChangeScene(SceneNumber nextScene)
{
// 	// Scene을 변경할때 같은 씬이면 변경하지 말자
// 	if (m_currentScene->GetSceneNum() == nextScene)
// 	{
// 		return;
// 	}

	m_objManager->id = 0;

	GameManager::GetInstance()->Finalize();
	SoundManager::GetInstance().ClearAudioComps();

	m_currentScene->EndLayer(0);
	m_renderer->DestroyAllObject();

	m_collisionDetectManager->Finalize();
	m_collisionDetectManager->Init();

	m_physicsManager->Finalize();
	m_physicsManager->Init();

	

	// 현재 scene을 바꾸고
	m_currentScene = m_sceneMap[nextScene];
	m_currentScene->SetRenderer(m_renderer);

	// 바꾼 scene에 대해서 초기화한다. 
	m_currentScene->EditScene(m_resourceManager, m_objManager, m_timeManager, m_collisionDetectManager, m_physicsManager);// , m_inputManager);
	m_currentScene->Awake();
	m_currentScene->Start();
		
}

void SceneManager::EndScene()
{
	m_currentScene->End();
}

void SceneManager::SetCurrentScene(SceneNumber sceneNum)
{
	m_currentScene = m_sceneMap[sceneNum];
}

