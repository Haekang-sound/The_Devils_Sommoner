#include "pch.h"
#include "TestScene.h"

// 매니저
#include "EngineObjectManager.h"
#include "EngineResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"

// 오브젝트
#include "GameObject.h"

// 컴포넌트
#include "Transform.h"
//#include "BackGround.h"
#include "RenderComponent.h"
#include "Time.h"
#include "AudioComponent.h"

// 리소스
#include "Image.h"
#include "TestType.h"

TestScene::TestScene()
{

}

TestScene::~TestScene()
{

}

void TestScene::EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager)
{
	// Scene 생성에 필요한 매니저 이식
	m_resourceManager = resourceManager;
	m_objManager = objManager;
	m_timeManager = timeManager;
	//m_inputManager = inputManger;

	// 리소스매니저에 리소스를 생성 및 저장한다.
	m_resourceManager->LoadResource<Image>("Mockery");		// Image
	m_resourceManager->LoadResource<Image>("umappyoi_1");	// 
	m_resourceManager->LoadResource<Audio>("umappyoi");		// Audio


	/// 배경을 그리는 오브젝트
	{
		// 오브젝트를 생성한다.
		m_object = m_objManager->CreateObject();

		// 오브젝트에 컴포넌트를 추가한다.
		m_object->AddComponent<Transform, /*BackGround, */RenderComponent, AudioComponent>();

		// 컴포넌트를 Get해서 정보들을 세팅한다.
		//m_object->GetComponent<Sprite>()->m_currentBitmap = m_resourceManager->GetResource<Image>("Mockery")->m_type->m_data;

		// Background는 이제 실제로 뭔가를 그리는 무언가를 해야할 것 같다
		// 때문에 background는 오브젝트를 알고 있고 내부에서 직접 컴포넌트를 얻어가면서 무언가를 한다.
		//m_object->GetComponent<BackGround>()->m_inputmanager = m_inputManager;
		//m_object->GetComponent<AudioComponent>()->m_sound = m_resourceManager->GetResource<Audio>("umappyoi")->m_type->m_data;
		//m_object->GetComponent<AudioComponent>()->m_soundKSL = m_soundKSL;

		// 리소스를 얻기위해 리소스매니저가 필요하다.
		//m_object->GetComponent<BackGround>()->m_resourceManager = m_resourceManager;

		// 오브젝트를 Scene에 추가한다.
		m_objects.push_back(m_object);

	}

}

void TestScene::Awake()
{

}

void TestScene::Start()
{
}

void TestScene::Update(float dTime)
{
}

void TestScene::LateUpdate(float dTime)
{
}

void TestScene::Render()
{
}

void TestScene::End()
{
}

void TestScene::EndLayer(unsigned int _layer)
{
	m_objManager->ReleaseLayer(_layer); // 오브젝트매니저가 레이어 단위로 정리한다
	m_objects.clear();	// scene의 내용은 클리어한다
}

SceneNumber TestScene::GetSceneNum()
{
	return m_myNum;
}

void TestScene::FixedUpdate(float dTime)
{

}

