 #include "pch.h"
#include "ExampleScene.h"
#include "GameObject.h"

#include "Transform.h"
#include "BackGround.h"
#include "Sprite.h"
#include "Text.h"
#include "Printer.h"
#include "RenderComponent.h"
#include "Time.h"
#include "TimeUpdater.h"

// 리소스
#include "Image.h"

ExampleScene::ExampleScene()
	: m_object(nullptr),
	m_resourceManager(nullptr), m_objManager(nullptr), m_timeManager(nullptr),
	m_objects{}
{

}

ExampleScene::~ExampleScene()
{

}

void ExampleScene::Start(ResourceManager* resourceManager, ObjectManager* objManager, TimeManager* timeManager)
{
	m_resourceManager = resourceManager;
	m_objManager = objManager;
	m_timeManager = timeManager;

	// 리소스매니저에 리소스를 생성 및 저장한다.
	m_resourceManager->LoadResource<Image>("Mockery");		// Image
	m_resourceManager->LoadResource<Image>("umappyoi_1");	// 
	m_resourceManager->LoadResource<Audio>("umappyoi");		// Audio


	/// 배경을 그리는 오브젝트
	{
		// 오브젝트를 생성한다.
		m_objManager->CreateObject();

		// 오브젝트에 컴포넌트를 추가한다.
		// 가변인자 템플릿을 이용하서 여러자료형을 한 번에 갖는 오브젝트를 만든다.
		m_objManager->AddComponent<Transform, BackGround, Sprite, RenderComponent>();

		// 오브젝트를 Scene에 추가한다.
		m_objects.push_back(m_objManager->GetObject());

		// 컴포넌트를 Get해서 정보들을 세팅한다.
		m_objManager->GetObject()->GetComponent<Transform>()->SetPos({ 0,0 });
		m_objManager->GetObject()->GetComponent<Transform>()->SetRectSize({ 0, 0 ,1000, 721 });
		m_objManager->GetObject()->GetComponent<Sprite>()->m_currentBitmap
			= m_resourceManager->GetResource<Image>("umappyoi_1")->m_resource->m_data;

		// Background는 이제 실제로 뭔가를 그리는 무언가를 해야할 것 같다
		// 때문에 background는 오브젝트를 알고 있고 내부에서 직접 컴포넌트를 얻어가면서 무언가를 한다.
		m_objManager->GetObject()->GetComponent<BackGround>()->m_obj = m_objManager->GetObject();

		// 리소스를 얻기위해 리소스매니저가 필요하다.
		m_objManager->GetObject()->GetComponent<BackGround>()->m_resourceManager = m_resourceManager;
		m_objManager->GetObject()->GetComponent<BackGround>()->m_drawSet = m_drawSet;
	}

	/// 텍스트를 출력하는 오브젝트
	{
		// 오브젝트를 생성한다.
		m_objManager->CreateObject();
		// 오브젝트에 컴포넌트를 추가한다.
		m_objManager->AddComponent<Transform, Text, Printer>();

		// 오브젝트를 Scene에 추가한다.
		m_objects.push_back(m_objManager->GetObject());

		// Printer로 그리기로 정했다.
		// 때문에 프린터에는 다른 컴포넌트를 사용할 수 있는 오브젝트 포인터가 필요하다
		m_objManager->GetObject()->GetComponent<Transform>()->SetPos({ 200, 200 });
		m_objManager->GetObject()->GetComponent<Text>()->str = L"exampleScnene에 오신 것을 환영합니다.";
		m_objManager->GetObject()->GetComponent<Printer>()->m_obj = m_objManager->GetObject();
		m_objManager->GetObject()->GetComponent<Printer>()->m_drawSet = m_drawSet;
	}

	/// DeltaTime을 출력하는 오브젝트
	{
		// 오브젝트를 생성한다.
		m_objManager->CreateObject();

		// 오브젝트에 컴포넌트를 추가한다.
		m_objManager->AddComponent<Transform, Text, Time, TimeUpdater, Printer>();

		// 오브젝트를 Scene에 추가한다.
		m_objects.push_back(m_objManager->GetObject());

		// Printer로 그리기로 정했다.
		// 때문에 프린터에는 다른 컴포넌트를 사용할 수 있는 오브젝트 포인터가 필요하다
		m_objManager->GetObject()->GetComponent<Transform>()->SetPos({ 700, 400 });
		m_objManager->GetObject()->GetComponent<Time>()->m_Timemanager = m_timeManager;
		m_objManager->GetObject()->GetComponent<TimeUpdater>()->m_obj = m_objManager->GetObject();
		m_objManager->GetObject()->GetComponent<Printer>()->m_obj = m_objManager->GetObject();
		m_objManager->GetObject()->GetComponent<Printer>()->m_drawSet = m_drawSet;

	}

	/// FPS를 출력하는 오브젝트
	{
		// 오브젝트를 생성한다.
		objManager->CreateObject();

		// 오브젝트에 컴포넌트를 추가한다.
		objManager->AddComponent<Transform, Text, Time, Printer>();

		// 오브젝트를 Scene에 추가한다.
		m_objects.push_back(objManager->GetObject());

		objManager->GetObject()->GetComponent<Transform>()->SetPos({ 900, 400 });

		// Printer로 그리기로 정했다.
		// 때문에 프린터에는 다른 컴포넌트를 사용할 수 있는 오브젝트 포인터가 필요하다
		objManager->GetObject()->GetComponent<Time>()->m_Timemanager = m_timeManager;
		objManager->GetObject()->GetComponent<Printer>()->m_obj = m_objManager->GetObject();
		objManager->GetObject()->GetComponent<Printer>()->m_drawSet = m_drawSet;
	}

}

void ExampleScene::Update(float dTime)
{
	for (auto e : m_objects)
	{
		e->Update(dTime);
	}
}

void ExampleScene::Render(ID3DRenderer* renderer)
{
	for (auto e : m_objects)
	{
		e->Render(renderer);
	}
}

void ExampleScene::End()
{
	for (auto e : m_objects)
	{
		e->ReleaseComponent();

		delete e;
	}
	m_objects.clear();

}
