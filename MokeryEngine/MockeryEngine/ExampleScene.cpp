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

// ���ҽ�
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

	// ���ҽ��Ŵ����� ���ҽ��� ���� �� �����Ѵ�.
	m_resourceManager->LoadResource<Image>("Mockery");		// Image
	m_resourceManager->LoadResource<Image>("umappyoi_1");	// 
	m_resourceManager->LoadResource<Audio>("umappyoi");		// Audio


	/// ����� �׸��� ������Ʈ
	{
		// ������Ʈ�� �����Ѵ�.
		m_objManager->CreateObject();

		// ������Ʈ�� ������Ʈ�� �߰��Ѵ�.
		// �������� ���ø��� �̿��ϼ� �����ڷ����� �� ���� ���� ������Ʈ�� �����.
		m_objManager->AddComponent<Transform, BackGround, Sprite, RenderComponent>();

		// ������Ʈ�� Scene�� �߰��Ѵ�.
		m_objects.push_back(m_objManager->GetObject());

		// ������Ʈ�� Get�ؼ� �������� �����Ѵ�.
		m_objManager->GetObject()->GetComponent<Transform>()->SetPos({ 0,0 });
		m_objManager->GetObject()->GetComponent<Transform>()->SetRectSize({ 0, 0 ,1000, 721 });
		m_objManager->GetObject()->GetComponent<Sprite>()->m_currentBitmap
			= m_resourceManager->GetResource<Image>("umappyoi_1")->m_resource->m_data;

		// Background�� ���� ������ ������ �׸��� ���𰡸� �ؾ��� �� ����
		// ������ background�� ������Ʈ�� �˰� �ְ� ���ο��� ���� ������Ʈ�� ���鼭 ���𰡸� �Ѵ�.
		m_objManager->GetObject()->GetComponent<BackGround>()->m_obj = m_objManager->GetObject();

		// ���ҽ��� ������� ���ҽ��Ŵ����� �ʿ��ϴ�.
		m_objManager->GetObject()->GetComponent<BackGround>()->m_resourceManager = m_resourceManager;
		m_objManager->GetObject()->GetComponent<BackGround>()->m_drawSet = m_drawSet;
	}

	/// �ؽ�Ʈ�� ����ϴ� ������Ʈ
	{
		// ������Ʈ�� �����Ѵ�.
		m_objManager->CreateObject();
		// ������Ʈ�� ������Ʈ�� �߰��Ѵ�.
		m_objManager->AddComponent<Transform, Text, Printer>();

		// ������Ʈ�� Scene�� �߰��Ѵ�.
		m_objects.push_back(m_objManager->GetObject());

		// Printer�� �׸���� ���ߴ�.
		// ������ �����Ϳ��� �ٸ� ������Ʈ�� ����� �� �ִ� ������Ʈ �����Ͱ� �ʿ��ϴ�
		m_objManager->GetObject()->GetComponent<Transform>()->SetPos({ 200, 200 });
		m_objManager->GetObject()->GetComponent<Text>()->str = L"exampleScnene�� ���� ���� ȯ���մϴ�.";
		m_objManager->GetObject()->GetComponent<Printer>()->m_obj = m_objManager->GetObject();
		m_objManager->GetObject()->GetComponent<Printer>()->m_drawSet = m_drawSet;
	}

	/// DeltaTime�� ����ϴ� ������Ʈ
	{
		// ������Ʈ�� �����Ѵ�.
		m_objManager->CreateObject();

		// ������Ʈ�� ������Ʈ�� �߰��Ѵ�.
		m_objManager->AddComponent<Transform, Text, Time, TimeUpdater, Printer>();

		// ������Ʈ�� Scene�� �߰��Ѵ�.
		m_objects.push_back(m_objManager->GetObject());

		// Printer�� �׸���� ���ߴ�.
		// ������ �����Ϳ��� �ٸ� ������Ʈ�� ����� �� �ִ� ������Ʈ �����Ͱ� �ʿ��ϴ�
		m_objManager->GetObject()->GetComponent<Transform>()->SetPos({ 700, 400 });
		m_objManager->GetObject()->GetComponent<Time>()->m_Timemanager = m_timeManager;
		m_objManager->GetObject()->GetComponent<TimeUpdater>()->m_obj = m_objManager->GetObject();
		m_objManager->GetObject()->GetComponent<Printer>()->m_obj = m_objManager->GetObject();
		m_objManager->GetObject()->GetComponent<Printer>()->m_drawSet = m_drawSet;

	}

	/// FPS�� ����ϴ� ������Ʈ
	{
		// ������Ʈ�� �����Ѵ�.
		objManager->CreateObject();

		// ������Ʈ�� ������Ʈ�� �߰��Ѵ�.
		objManager->AddComponent<Transform, Text, Time, Printer>();

		// ������Ʈ�� Scene�� �߰��Ѵ�.
		m_objects.push_back(objManager->GetObject());

		objManager->GetObject()->GetComponent<Transform>()->SetPos({ 900, 400 });

		// Printer�� �׸���� ���ߴ�.
		// ������ �����Ϳ��� �ٸ� ������Ʈ�� ����� �� �ִ� ������Ʈ �����Ͱ� �ʿ��ϴ�
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
