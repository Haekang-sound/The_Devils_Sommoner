#include "pch.h"
#include "HeartItem.h"
#include "GameObject.h"
#include "Transform.h"
#include "PlayerComponent.h"

#include "Ghost.h"
#include "DemonAltarComponent.h"
#include "GameManager.h"
#include "SoundManager.h"

HeartItem::HeartItem()
	: m_inverseNum(-1)
	//, m_maxSize(2.f)
	//, m_minSize(0.7f)
	, m_maxSize(0.09f)
	, m_minSize(0.04f)
	, m_heartBeatCycleTime(0.f)
	, m_currentHeartBeatTime(0.f)
{

}

HeartItem::~HeartItem()
{

}

void HeartItem::Start()
{
	//m_originScale = SimpleMath::Vector3(1.f);
	m_originScale = SimpleMath::Vector3(0.04f);

	m_heartTransform = m_modelObject->GetComponent<Transform>();
	//m_heartTransform = m_pOwner->GetComponent<Transform>();
	m_heartBeatSpeed = 20.f;
	//m_heartBeatSpeed = 0.2f;

	m_transform = m_pOwner->GetComponent<Transform>();

	//// TEST : 임의로 설정
	//SetHeartAltar(GameManager::GetInstance()->GetCurrentAltarObject());
	
	m_pOwner->GetComponent<Transform>()->SetLocalPosition({ -100.f, -100.f, -100.f });
	m_renderer->Send(2, m_modelObject->GetObjectID(), true, {});
}

void HeartItem::FixedUpdate(float dTime)
{

}

void HeartItem::Update(float dTime)
{
	if (GameManager::GetInstance()->GetGhostObject())
	{
		m_isDisturbing = GameManager::GetInstance()->GetGhostObject()->GetComponent<Ghost>()->GetDisturb();
	}
	if (!m_isDisturbing)
	{
		UpdateSpeedByDistanceValue();

		if (m_onHeartBeat)
		{
			SimpleMath::Vector3 scale = m_heartTransform->GetLocalScale();

			if (scale.x < m_minSize)
			{
				scale = SimpleMath::Vector3(m_minSize);
				m_inverseNum *= -1;
				m_onHeartBeat = false;
			}
			else if (scale.x > m_maxSize)
			{
				scale = SimpleMath::Vector3(m_maxSize);
				m_inverseNum *= -1;
			}
			scale += m_originScale * m_heartBeatSpeed * dTime * m_inverseNum;
			m_heartTransform->SetLocalScale(scale);
		}
		else
		{
			m_currentHeartBeatTime += dTime;
			if (m_currentHeartBeatTime >= m_heartBeatCycleTime)
			{
				
				if (GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->GetItemState() == 1)
					SoundManager::GetInstance().PlayDoor0(eSOUNDKIND::fHeart);
				
				m_onHeartBeat = true;
				m_currentHeartBeatTime = 0.f;
			}
		}
	}

}

void HeartItem::LateUpdate(float dTime)
{

}

void HeartItem::Render()
{

}

void HeartItem::Release()
{

}

void HeartItem::Select()
{
	m_pOwner->GetComponent<Transform>()->SetLocalPosition({ -0.5f,-0.7f, 1.7f });
}

void HeartItem::UnSelect()
{
	m_pOwner->GetComponent<Transform>()->SetLocalPosition({ -100.f, -100.f, -100.f });
}

void HeartItem::Act(GameObject* player)
{
	// 얜 딱히 하는 행동이 없음
}

void HeartItem::FindNextAltar()
{

}

void HeartItem::SetHeartModelObject(GameObject* heartModel)
{
	m_modelObject = heartModel;
}

void HeartItem::SetHeartBeatCycle(float time)
{
	//m_heartBeatCycleTime = time;
	m_originalHeartBeatCycleTime = time;
}

void HeartItem::SetHeartAltar(GameObject* heartAltar)
{
	if (!heartAltar)
		return;
	m_targetPosition = heartAltar->GetComponent<Transform>()->GetPosition();
	m_maxDistance = heartAltar->GetComponent<DemonAltarComponent>()->GetAffectDistanceRadius();
	//m_maxDistance = 100.f;
}

void HeartItem::UpdateSpeedByDistanceValue()
{
	m_nowPosition = m_transform->GetPosition();
	float x = fabs(m_targetPosition.x - m_nowPosition.x);
	float z = fabs(m_targetPosition.z - m_nowPosition.z);

	m_distance = x * x + z * z;
	if (fabs(m_maxDistance) <= 0.001f)
	{
		return;
	}
	m_ratio = m_distance / m_maxDistance;
	//m_ratio = 1.f - m_ratio;


	if (m_ratio >= 1.f)
	{
		m_heartBeatCycleTime = m_originalHeartBeatCycleTime;
		return;
	}
	//std::cout << "Heart Beat Distance Ratio : " << m_ratio << " And Time : " << m_heartBeatCycleTime << std::endl;
	m_heartBeatCycleTime = m_originalHeartBeatCycleTime * m_ratio;
}