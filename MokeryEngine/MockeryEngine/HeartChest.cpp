#include "pch.h"
#include "HeartChest.h"
#include "GameManager.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "Inventory.h"
#include "MeshRenderer.h"
#include "SoundManager.h"
#include "timer.h"
#include "EngineObjectManager.h"
HeartChest::HeartChest()
	: m_heartChestModel(nullptr)
	, m_isDisabled(false)
{

}

HeartChest::~HeartChest()
{

}

void HeartChest::Start()
{
	m_heartChestModel->GetComponent<MeshRenderer>()->StopAnimation();

}

void HeartChest::Update(float dTime)
{
	if (fabs(m_currentTime - m_beforeTime) < 0.0001f)
	{
		m_renderer->Send(1, m_heartChestModel->GetObjectID(), 0, { 0.f,0.f,0.f,1.f });
	}
}

void HeartChest::InteractAddTime(float dTime)
{
	if (!GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->GethaveHeart() && !m_isDisabled)
	{
		Super::InteractAddTime(dTime);

		UINT id = m_heartChestModel->GetObjectID();
		//float c = 140.f / 255.f;
		m_renderer->Send(1, id, m_currentTime / m_loadTime, { 1.f,1.f,1.f,1.f });
	}
}

void HeartChest::Interact()
{
	if (!(GetOwner()->GetObjectManager()->GetOBjectsByComponent<Timer>()->GetComponent<Timer>()->GetisCount()))
	{
		GetOwner()->GetObjectManager()->GetOBjectsByComponent<Timer>()->GetComponent<Timer>()->SetIsCountToggle();
	}
	GetOwner()->GetObjectManager()->GetOBjectsByComponent<Timer>()->GetComponent<Timer>()->AddTime(300.f);
	Super::Interact();
	//std::cout << "Heart Chest Interact!" << std::endl;
	SoundManager::GetInstance().PlaySFXR(eSOUNDKIND::fBox);

	GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->OnHeart();
	if (!GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->GetGameStart())
	{
		GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->SetGameStart(true);
	}
	m_isDisabled = true;
	m_heartChestModel->GetComponent<MeshRenderer>()->PlayAnimationOnce(0, false);
}

void HeartChest::SetHeartChestModel(GameObject* model)
{
	m_heartChestModel = model;
}
