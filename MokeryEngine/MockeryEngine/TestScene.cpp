#include "pch.h"
#include "TestScene.h"

// �Ŵ���
#include "EngineObjectManager.h"
#include "EngineResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"

// ������Ʈ
#include "GameObject.h"

// ������Ʈ
#include "Transform.h"
//#include "BackGround.h"
#include "RenderComponent.h"
#include "Time.h"
#include "AudioComponent.h"

// ���ҽ�
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
	// Scene ������ �ʿ��� �Ŵ��� �̽�
	m_resourceManager = resourceManager;
	m_objManager = objManager;
	m_timeManager = timeManager;
	//m_inputManager = inputManger;

	// ���ҽ��Ŵ����� ���ҽ��� ���� �� �����Ѵ�.
	m_resourceManager->LoadResource<Image>("Mockery");		// Image
	m_resourceManager->LoadResource<Image>("umappyoi_1");	// 
	m_resourceManager->LoadResource<Audio>("umappyoi");		// Audio


	/// ����� �׸��� ������Ʈ
	{
		// ������Ʈ�� �����Ѵ�.
		m_object = m_objManager->CreateObject();

		// ������Ʈ�� ������Ʈ�� �߰��Ѵ�.
		m_object->AddComponent<Transform, /*BackGround, */RenderComponent, AudioComponent>();

		// ������Ʈ�� Get�ؼ� �������� �����Ѵ�.
		//m_object->GetComponent<Sprite>()->m_currentBitmap = m_resourceManager->GetResource<Image>("Mockery")->m_type->m_data;

		// Background�� ���� ������ ������ �׸��� ���𰡸� �ؾ��� �� ����
		// ������ background�� ������Ʈ�� �˰� �ְ� ���ο��� ���� ������Ʈ�� ���鼭 ���𰡸� �Ѵ�.
		//m_object->GetComponent<BackGround>()->m_inputmanager = m_inputManager;
		//m_object->GetComponent<AudioComponent>()->m_sound = m_resourceManager->GetResource<Audio>("umappyoi")->m_type->m_data;
		//m_object->GetComponent<AudioComponent>()->m_soundKSL = m_soundKSL;

		// ���ҽ��� ������� ���ҽ��Ŵ����� �ʿ��ϴ�.
		//m_object->GetComponent<BackGround>()->m_resourceManager = m_resourceManager;

		// ������Ʈ�� Scene�� �߰��Ѵ�.
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
	m_objManager->ReleaseLayer(_layer); // ������Ʈ�Ŵ����� ���̾� ������ �����Ѵ�
	m_objects.clear();	// scene�� ������ Ŭ�����Ѵ�
}

SceneNumber TestScene::GetSceneNum()
{
	return m_myNum;
}

void TestScene::FixedUpdate(float dTime)
{

}

