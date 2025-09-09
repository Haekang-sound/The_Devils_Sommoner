#include "pch.h"
#include "ItemChest.h"
#include <iostream>
#include "GameObject.h"
#include "RandomNumber.h"
#include "PlayerComponent.h"
#include "Timer.h"
#include "GameManager.h"
#include "EngineObjectManager.h"
#include "MeshRenderer.h"
#include "SoundManager.h"

float ItemChest::m_staticpassingTime = 0.f;

ItemChest::ItemChest()
	: InteractiveObject()
	, m_passingTime(0.f), m_isActivated(false)
	, m_player(nullptr), m_itemType(ItemList::xRay)
	, m_isDisabled(false), m_isOpen(false)
	, m_forSound(false)
{

}

ItemChest::~ItemChest()
{

}

void ItemChest::Awake()
{


}

void ItemChest::Start()
{
	m_itemChestModel->GetComponent<MeshRenderer>()->StopAnimation();
	m_player = GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>();

	m_player = GetOwner()->GetObjectManager()->GetOBjectsByComponent<PlayerComponent>()->GetComponent<PlayerComponent>();
	m_timer = GameManager::GetInstance()->GetTimerComponent();
}

void ItemChest::FixedUpdate(float dTime)
{

}

void ItemChest::Update(float dTime)
{
	if (fabs(m_currentTime - m_beforeTime) < 0.0001f)
	{
		m_renderer->Send(1, m_itemChestModel->GetObjectID(), 0, { 0.f,0.f,0.f,1.f });
	}

	// 박스는 기본적으로 닫혀있다.
	if (m_isActivated)
	{
		switch (m_itemType)
		{
		case ItemList::Heal:
			// 체력 전부 회복
			if (!m_forSound)
			{
				SoundManager::GetInstance()->PlayDoor2(eSOUNDKIND::fBuff);
				m_forSound = true;
			}
			m_player->SetHp(100.f);
			//std::cout << "Heal" << std::endl;
			m_isActivated = false;
			break;

		case ItemList::xRay:
			// TODO : 제단 위치 엑스레이
			if (!m_forSound)
			{
				SoundManager::GetInstance()->PlayDoor2(eSOUNDKIND::fBuff);
				m_forSound = true;
			}
			m_passingTime += dTime;
			//std::cout << "xRay" << std::endl;
			if (m_passingTime >= 30.f)
			{
				//std::cout << "off" << std::endl;
				// 원래대로
				m_passingTime = 0.f;
				m_isActivated = false;
			}
			break;

		case ItemList::SpeedUp:
			// 플레이어 이속 증가
			if (!m_forSound)
			{
				SoundManager::GetInstance()->PlayDoor2(eSOUNDKIND::fBuff);
				m_forSound = true;
			}
			m_player->SetMoveSpeed(2.f, 4.f);
			m_staticpassingTime += dTime;
			//std::cout << "SpeedUp" << std::endl;
			if (m_staticpassingTime >= 30.f)
			{
				m_player->SetMoveSpeed(1.f, 2.f);
				//std::cout << "off" << std::endl;
				m_staticpassingTime = 0.f;
				m_isActivated = false;
			}
			break;

		case ItemList::SpeedDown:
			// 플레이어 이속 감소
			if (!m_forSound)
			{
				SoundManager::GetInstance()->PlayDoor2(eSOUNDKIND::fDebuff);
				m_forSound = true;
			}
			m_player->SetMoveSpeed(0.5f, 1.f);
			m_staticpassingTime += dTime;
			//std::cout << "SpeedDown" << std::endl;
			if (m_staticpassingTime >= 30.f)
			{
				m_player->SetMoveSpeed(1.f, 2.f);
				//std::cout << "off" << std::endl;
				m_staticpassingTime = 0.f;
				m_isActivated = false;
			}
			break;

		case ItemList::LostTime:
			// TODO : 시간 단축 
			if (!m_forSound)
			{
				SoundManager::GetInstance()->PlayDoor2(eSOUNDKIND::fDebuff);
				m_forSound = true;
			}
			//std::cout << "LostTime" << std::endl;
			if (m_timer)
			{
				m_timer->SubTime(10.f);
			}
			m_isActivated = false;
			break;
		}
	}
}

void ItemChest::LateUpdate(float dTime)
{
	// 반드시 넣어주어야 한다!
	Super::LateUpdate(dTime);




	// Test
	if (m_itemChestModel->GetComponent<MeshRenderer>()->IsFinishAnimation())
	{
		m_itemChestModel->GetComponent<MeshRenderer>()->StopAnimation();
	}
}

void ItemChest::Render()
{

}

void ItemChest::Release()
{
	m_staticpassingTime = 0.f;
}

void ItemChest::InteractAddTime(float dTime)
{
	if (!m_isDisabled)
	{
		Super::InteractAddTime(dTime);
		UINT id = m_itemChestModel->GetObjectID();
		float c = 140.f / 255.f;

		m_renderer->Send(1, id, m_currentTime / m_loadTime, { 1.f,1.f,1.f,1.f });
	}
}

void ItemChest::Interact()
{
	Super::Interact();
	m_isOpen = true; // 사용되는 시점에 박스는 열린다.
	m_isActivated = true;
	m_isDisabled = true;
	m_staticpassingTime = 0.f;
	m_passingTime = 0.f;
	m_itemChestModel->GetComponent<MeshRenderer>()->PlayAnimationOnce(0, false);
	SoundManager::GetInstance()->PlaySFXR(eSOUNDKIND::fBox);
	//SoundManager::GetInstance()->AddReverb(SoundManager::GetInstance()->GetSFXRChannel());

}

void ItemChest::SetItemChestModelObject(GameObject* model)
{
	m_itemChestModel = model;
}

void ItemChest::SetRandomItemType()
{
	int randomInt = m_pOwner->GetComponent<RandomNumber>()->GetRandomInt(1, 100);
	if (1 <= randomInt && randomInt <= 26)
	{
		m_itemType = ItemList::Heal;
		//std::cout << "Heal" << std::endl;
	}

	else if (27 <= randomInt && randomInt <= 53)
	{
		m_itemType = ItemList::xRay;
		//std::cout << "xRay" << std::endl;
	}

	else if (54 <= randomInt && randomInt <= 80)
	{
		m_itemType = ItemList::SpeedUp;
		//std::cout << "SpeedUp" << std::endl;
	}

	else if (81 <= randomInt && randomInt <= 90)
	{
		m_itemType = ItemList::SpeedDown;
		//std::cout << "SpeedDown" << std::endl;
	}

	else if (91 <= randomInt && randomInt <= 100)
	{
		m_itemType = ItemList::LostTime;
		//std::cout << "LostTime" << std::endl;
	}

}
