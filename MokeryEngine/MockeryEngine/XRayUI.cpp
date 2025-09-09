#include "pch.h"
#include "XRayUI.h"
#include "EngineObjectManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "PlayerComponent.h"
#include "DemonAltarComponent.h"
#include "inputmanager.h"
#include "GameManager.h"
#include "ItemChest.h"



XRayUI::XRayUI()
{

}

XRayUI::~XRayUI()
{

}

void XRayUI::Start()
{

	// obj벡터를 순회면서 itemchset를 찾는다.

	auto vec = GetOwner()->GetObjectManager()->GetObjects();
	for (auto& e : vec)
	{
		// xray 를 갖는 컴포넌트들을 가져온다.
		if (e->GetComponent<ItemChest>() != nullptr)
		{
			if (ItemList::xRay == e->GetComponent<ItemChest>()->GetItemType())
			{
				m_itemChests.push_back(e->GetComponent<ItemChest>());
			}
		}
	}

	GetOwner()->SetParentByName("Player");
	//m_renderer->Send(0, GetOwner()->GetObjectID(), 0, { 1.f,0.f,0.f,1.f });
	m_camTransform = GetOwner()->GetObjectManager()->GetOBjectsByComponent<PlayerComponent>()->GetComponent<Transform>();
	m_alterTransform = GameManager::GetInstance()->GetCurrentAltarObject()->GetComponent<Transform>();

	//m_renderer->CreateSprite(&assetNum, GetOwner()->GetObjectID(), &m_worldTM, &m_size, &m_state, GetOwner()->GetIsDraw());
}

void XRayUI::FixedUpdate(float dTime)
{

}

void XRayUI::Update(float dTime)
{

	// 	unsigned int id = GameManager::GetInstance()->GetCurrentAltarObject()->GetComponent<DemonAltarComponent>()->GetAltarModel()->GetObjectID();
	// 	if (InputManager::GetInstance()->m_Keyboard.IsKeydown('0'))
	// 	{
	// 		m_renderer->Send(1, id, true, { 1.f,0.f,0.f,0.f });
	// 		m_renderer->Send(2, id, true, { 1.f,0.f,0.f,0.f });
	// 	}
	// 	if (InputManager::GetInstance()->m_Keyboard.IsKeyUp('0'))
	// 	{
	// 		m_renderer->Send(1, id, true, { 0.f,0.f,0.f,1.f });
	// 		m_renderer->Send(2, id, false, { 1.f,0.f,0.f,0.f });
	// 	}

	//	for (auto& e : m_itemChests)
	//	{
	//		// 	m_isOpen가 true일 때
	//		unsigned int id = GameManager::GetInstance()->GetCurrentAltarObject()->GetComponent<DemonAltarComponent>()->GetAltarModel()->GetObjectID();
	//		if (e->GetisActivated())
	//		{
	//			GameManager::GetInstance()->GetCurrentAltarObject()->GetComponent<DemonAltarComponent>()->DrawSphere();
	//// 			m_renderer->Send(1, id , true, { 1.f,0.f,0.f,0.f });
	//// 			m_renderer->Send(2, id , true, { 1.f,0.f,0.f,0.f });
	//		}
	//		else
	//		{
	//			GameManager::GetInstance()->GetCurrentAltarObject()->GetComponent<DemonAltarComponent>()->DoNotDrawSphere();
	//
	//// 			m_renderer->Send(1, id, true, { 0.f,0.f,0.f,1.f });
	//// 			m_renderer->Send(2, id, false, { 1.f,0.f,0.f,0.f });
	//		}
	//	}
}

void XRayUI::LateUpdate(float dTime)
{
	for (auto& e : m_itemChests)
	{
		// 	m_isOpen가 true일 때
		unsigned int id = GameManager::GetInstance()->GetCurrentAltarObject()->GetComponent<DemonAltarComponent>()->GetAltarModel()->GetObjectID();
		if (e->GetisActivated())
		{
			GameManager::GetInstance()->GetCurrentAltarObject()->GetComponent<DemonAltarComponent>()->DrawSphere();
			// 			m_renderer->Send(1, id , true, { 1.f,0.f,0.f,0.f });
			// 			m_renderer->Send(2, id , true, { 1.f,0.f,0.f,0.f });
		}
		else
		{
			GameManager::GetInstance()->GetCurrentAltarObject()->GetComponent<DemonAltarComponent>()->DoNotDrawSphere();

			// 			m_renderer->Send(1, id, true, { 0.f,0.f,0.f,1.f });
			// 			m_renderer->Send(2, id, false, { 1.f,0.f,0.f,0.f });
		}
	}
}

void XRayUI::Render()
{
}

void XRayUI::Release()
{
}
