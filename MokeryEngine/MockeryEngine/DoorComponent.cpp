#include "pch.h"
#include "DoorComponent.h"
#include "AudioComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "TitleScene.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"
#include "BoxCollision.h"

// TEST
#include "InputManager.h"
#include "SoundManager.h"

DoorComponent::DoorComponent()
	: m_door(nullptr),
	m_doorModel(nullptr),
	m_doorState(DoorState::Close),
	m_doorSpeed(5.f),
	m_maxAngle(90.f)
{
	m_maxAngleToRadian = m_maxAngle * 3.141592f / 180.f;
}

DoorComponent::~DoorComponent()
{

}

void DoorComponent::Start()
{

}

void DoorComponent::FixedUpdate(float dTime)
{
	// fixed update
	// 알아서 잘 해보도록
}

void DoorComponent::Update(float dTime)
{
	if (fabs(m_currentTime - m_beforeTime) < 0.0001f)
	{
		m_renderer->Send(1, m_doorModel->GetObjectID(), 0, { 0.f,0.f,0.f,1.f });
	}
	//m_renderer->Send(1, m_doorModel->GetObjectID(), 0, { 0.f,0.f,0.f,1.f });
	// interact로 문을 열었을 경우에만 isActivated가 켜짐
	if (isActivated)
	{
		Transform* transform = m_door->GetComponent<Transform>();
		SimpleMath::Vector3 rot = transform->GetLocalRotation();
		switch (m_doorState)
		{
			case DoorState::Open:
			{
				//std::cout << "door open : " << rot.y << std::endl;
				if (rot.y < m_maxAngleToRadian)
				{
					rot.y += m_doorSpeed * dTime;
					transform->SetLocalRotation(rot);
				}
				else
				{
					isActivated = false;
				}
			}
			break;
			case DoorState::Close:
			{
				//std::cout << "door close : " << rot.y << std::endl;
				if (rot.y > 0.f)
				{
					rot.y -= m_doorSpeed * dTime;
					transform->SetLocalRotation(rot);
				}
				else
				{
					isActivated = false;
				}
			}
			break;
			default:
				break;
		}
	}
}

void DoorComponent::LateUpdate(float dTime)
{
	Super::LateUpdate(dTime);
	/*if(!m_isInteract)
	{
		m_renderer->Send(1, m_doorModel->GetObjectID(), 0, { 0.f,0.f,0.f,1.f });
	}*/
}

void DoorComponent::Render()
{

}

void DoorComponent::Release()
{

}

void DoorComponent::Interact()
{
	Super::Interact();
	isActivated = true;
	if (m_doorState == DoorState::Close)
	{
		/// TODO : 어떻게든 순서를 받아서
		/// 만들어놓은 채널에 와르르 설정되게 해야된다.
		m_doorState = DoorState::Open;
		m_pOwner->GetComponent<BoxCollision>()->SetCollisionWith(CollisionWith::OnlyRay);
		int count = 4;
		for (auto e : SoundManager::GetInstance().GetAudioComps())
		{
			if (GetOwner() == SoundManager::GetInstance().GetAudioComps()[count])
			{
				SoundManager::GetInstance().DoorOpen(count);
				break;
			}
			count++;
		}
	}
	else
	{
		m_doorState = DoorState::Close;
		m_pOwner->GetComponent<BoxCollision>()->SetCollisionWith(CollisionWith::All);
		SoundManager::GetInstance().PlaySFX(eSOUNDKIND::fClose);
		//int count = 4;
		/*for (auto e : SoundManager::GetInstance().GetAudioComps())
		{
			if (GetOwner() == SoundManager::GetInstance().GetAudioComps()[count])
			{
				SoundManager::GetInstance().DoorClose(count);
				continue;
			}
			count++;
		}*/
	}
}

void DoorComponent::InteractAddTime(float dTime)
{
	
	Super::InteractAddTime(dTime);

	UINT id = m_doorModel->GetObjectID();
	//float c = 140.f / 255.f;
	m_renderer->Send(1, id, m_currentTime / m_loadTime, { 1.f,1.f,1.f,1.f });
	//std::cout << "ID : " << id << std::endl;
}

void DoorComponent::SetDoorObject(GameObject* door)
{
	m_door = door;
}

const DoorState& DoorComponent::GetDoorState()
{
	return m_doorState;
}

void DoorComponent::SetDoorModelObject(GameObject* door)
{
	m_doorModel = door;
}
