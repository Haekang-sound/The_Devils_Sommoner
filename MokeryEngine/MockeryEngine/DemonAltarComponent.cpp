#include "pch.h"
#include "DemonAltarComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "HeartComponent.h"
#include "GameManager.h"
#include "PlayerComponent.h"
#include "Item.h"
#include "SoundManager.h"
#include "timer.h"
#include "EngineObjectManager.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"

using namespace DirectX;

int DemonAltarComponent::m_altarCount = 0;



DemonAltarComponent::DemonAltarComponent()
	: m_isActivated(false), m_isDisabled(false)
	, m_sequence(AltarSequence::NONE)
	, m_affectDistanceRadius(100.f)
	, m_altarModel(nullptr)
	, m_isFadeIn(false)
	, m_isFadeOut(false)
{

}

DemonAltarComponent::~DemonAltarComponent()
{

}

void DemonAltarComponent::Start()
{
	//m_heartSign->SetIsDraw(false);
}

void DemonAltarComponent::FixedUpdate(float dTime)
{

}

void DemonAltarComponent::Update(float dTime)
{
	if (fabs(m_currentTime - m_beforeTime) < 0.0001f)
	{
		m_renderer->Send(1, m_altarModel->GetObjectID(), 0, { 0.f,0.f,0.f,1.f });
	}

}

void DemonAltarComponent::LateUpdate(float dTime)
{
	Super::LateUpdate(dTime);
	m_passingtime += dTime;
	if (m_isActivated && !m_isDisabled)
	{
		m_isDisabled = true;
		m_isActivated = false;
	}
	if (m_isDisabled && !m_isFadeIn)
	{
		m_renderer->Send(0, 0, 0, { 0.f,0.f,0.f,1.f });
		if (!m_isFadeIn)
			m_passingtime = 0.f;
		m_isFadeIn = true;
	}
	if (m_isFadeIn && !m_isFadeOut)
	{
		m_renderer->Send(0, 0, 0, { m_passingtime / 3.f,m_passingtime / 3.f,m_passingtime / 3.f,1.f });
		if (m_passingtime > 3.f)
		{
			m_isFadeOut = true;
		}
	}
}

void DemonAltarComponent::Render()
{

}

void DemonAltarComponent::Release()
{
	m_altarCount = 0;
}

void DemonAltarComponent::Interact()
{
	Super::Interact();
	SoundManager::GetInstance()->PlayDemon();
	SoundManager::GetInstance()->AddReverb(SoundManager::GetInstance()->GetDemonChannel());
	SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetDoor3Channel());

	if (GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->GethaveHeart())
	{
		if (m_altarCount == static_cast<int>(m_sequence))
		{
			if (!m_isDisabled)
			{
				m_isActivated = true;
				m_altarCount++;
				//GetOwner()->GetObjectManager()->GetOBjectsByComponent<Timer>()->GetComponent<Timer>()->AddTime(500.f);
				GameManager::GetInstance()->SetNextAltar(m_altarCount);
				GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->SethaveHeart(false);
				GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->SetItemState(0);
				m_pOwner->GetComponent<Transform>()->SetPosition({ -100.f,-100.f,-100.f });
			}
		}
	}
}

void DemonAltarComponent::InteractAddTime(float dTime)
{

	if (m_altarCount != static_cast<int>(m_sequence))
		return;
	if (!m_isDisabled)
	{
		Super::InteractAddTime(dTime);
		UINT id = m_altarModel->GetObjectID();
		UINT id2 = GameManager::GetInstance()->GetPlayerObject()->GetObjectID();
		int hp = GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->GetHp();
		//m_renderer->Send(1, id, m_currentTime / m_loadTime, { 1.f,0.3f,0.3f,1.f });
		m_renderer->Send(1, id, m_currentTime / m_loadTime, { 117.f / 255.f,2.f / 255.f,4.f / 255.f,1.f });
	}
}

float DemonAltarComponent::GetAffectDistanceRadius()
{
	return m_affectDistanceRadius;
}

void DemonAltarComponent::SetAffectDistanceRadius(float distance)
{
	m_affectDistanceRadius = distance;
}

void DemonAltarComponent::DrawSphere()
{
	SimpleMath::Vector3 currentPos = m_pOwner->GetComponent<Transform>()->GetPosition();
	//m_renderer->DrawDebugingBoundingSphere({ currentPos.x, currentPos.y + 1.f, currentPos.z },0.8f, { 1.0f,0.f,0.f,1.f });
	//m_heartSign->SetIsDraw(true);
	m_renderer->Send(2, m_altarModel->GetObjectID(), true, {});
	m_renderer->Send(2, m_heartSign->GetObjectID(), true, {});
}

void DemonAltarComponent::DoNotDrawSphere()
{
	m_renderer->Send(2, m_altarModel->GetObjectID(), false, {});
	m_renderer->Send(2, m_heartSign->GetObjectID(), false, {});
	//m_heartSign->SetIsDraw(false);
}

void DemonAltarComponent::SetHeartSignModel(GameObject* obj)
{
	m_heartSign = obj;
	//m_heartSign->SetIsDraw(false);
}

GameObject* DemonAltarComponent::GetAltarModel()
{
	return m_altarModel;
}

void DemonAltarComponent::SetAltarModel(GameObject* model)
{
	m_altarModel = model;
}
