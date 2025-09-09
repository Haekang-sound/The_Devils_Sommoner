#include "pch.h"
#include "PlayerComponent.h"
#include "Collision.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "RayComponent.h"
#include "Transform.h"
#include "SphereCollision.h"
#include "EnemyComponent.h"
#include "InputManager.h"
#include "InteractiveObject.h"
#include "ItemChest.h"
#include "Item.h"
#include "Inventory.h"
#include "DemonAltarComponent.h"
#include "HeartChest.h"
#include "SoundManager.h"
#include "timer.h"
#include "EngineObjectManager.h"


PlayerComponent::PlayerComponent()
	: m_hp(100.f), m_walkSpeed(0.f)
	, m_stamina(0.f), m_maxStamina(0.f), m_minStamina(0.f)
	, m_isRunning(false), m_isInteracting(false)
	, m_isBeforeInteracting(false)
	, m_isHandedKnife(true), m_isHandedItem(false)
	, m_moveSpeed(0.f), m_runSpeed(0.f)
	, m_pos(), m_camera(nullptr)
	, m_selectedItem(nullptr)
	, m_inventory(nullptr)
	, m_haveKnife(false)
	, m_haveHeart(false)
	, m_passingTime(0.f)
	, m_knifeCoolTime(30.f)
	, m_isGameStarted(false)
	, m_isStaminaZero(false)
	, m_holdHeart(false)
	, m_isExhausted(false)
	, m_isKnifeReady(false)
	, m_knifeAnimationFinishTime(1.5f)
	, m_knifeAnimationCurrentTime(0.f)
{

}

PlayerComponent::~PlayerComponent()
{

}

void PlayerComponent::Start()
{
	m_inventory = m_pOwner->GetComponent<Inventory>();
	m_camera = m_pOwner->GetComponent<CameraComponent>();

	m_hp = 99.f;
	
	m_walkSpeed = 1.f;
	m_runSpeed = 2.f;

	
	m_stamina = 5.f;
	m_maxStamina = 5.f;
	m_minStamina = 0.f;
	m_fov = 60;

	
	m_camera->SetFov(m_fov);

}

void PlayerComponent::FixedUpdate(float dTime)
{

}

void PlayerComponent::Update(float dTime)
{
	CheckInteractiveObject(dTime);


	//std::cout<< "player stamia : " << m_stamina <<  ", obID : "<< GetOwner()->GetObjectID()<< std::endl;

	m_moveSpeed = m_walkSpeed;

	if (m_stamina > 5.f)
	{
		m_stamina = 5.f;
	}

	m_staminaCoolTime += dTime;


	if (m_staminaCoolTime > 2.f && m_stamina > 0.f)
	{
		SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetDoor39Channel());

		if (InputManager::GetInstance()->m_Keyboard.IsKeyHold(Keyboard::LeftShift)
			&& InputManager::GetInstance()->m_Keyboard.IsKeyHold(Keyboard::W))
		{
			m_stamina -= dTime * 2;
			m_moveSpeed = m_runSpeed;
			m_isStaminaZero = false;
		}
	}

	else if (m_stamina <= 0.f && !m_isStaminaZero)
	{
		if (!m_isExhausted)
		{
			SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetDoor39Channel());
			SoundManager::GetInstance()->PlayDoor39(eSOUNDKIND::lExhausted);
			m_isExhausted = true;
		}
		m_isStaminaZero = true;
		m_staminaCoolTime = 0.f;
	}

	if (m_stamina <= 5.f && m_stamina > 0.f)
	{
		m_stamina += dTime;
	}

	if (m_isStaminaZero)
	{
		if (m_staminaCoolTime > 1.f)
		{

			if (m_stamina <= 5.f)
			{
				m_isExhausted = false;
				m_stamina += dTime;
			}
			m_isStaminaZero = false;
		}
	}

	// 단검 던지는 애니메이션 중일때는 아이템을 바꿔끼지 맙시다
	if (m_isKnifeAnimationPlaying)
	{
		m_knifeAnimationCurrentTime += dTime;
		if (m_knifeAnimationCurrentTime >= m_knifeAnimationFinishTime)
		{
			m_knifeAnimationCurrentTime = 0.f;
			m_isKnifeAnimationPlaying = false;
		}
	}
	// 단검
	//if (InputManager::GetInstance()->m_Keyboard.IsKeydown('1'))
	if (InputManager::GetInstance()->m_Mouse.IsButtonHold(InputManager::GetInstance()->m_Mouse.rightButton)
		&& !m_isKnifeAnimationPlaying)
	{

		m_itemState = 0;
		if (m_selectedItem)
			m_selectedItem->UnSelect();
		m_selectedItem = m_inventory->SelectItem(0);
		if (m_selectedItem)
			m_selectedItem->Select();
	}
	// 심장
	if (m_haveHeart)
	{
		m_itemState = 1;
		//if (InputManager::GetInstance()->m_Keyboard.IsKeydown('2'))
		if (!InputManager::GetInstance()->m_Mouse.IsButtonHold(InputManager::GetInstance()->m_Mouse.rightButton)
			&& !m_isInteracting
			&& !m_isKnifeAnimationPlaying)
		{
			if (m_selectedItem)
				m_selectedItem->UnSelect();
			m_selectedItem = m_inventory->SelectItem(1);
			if (m_selectedItem)
				m_selectedItem->Select();
			
			m_camera->SetFov(m_fov);
			// 단검을 선택 안했을 경우 그냥 디폴트는 심장
			//m_camera->SetFov(m_fov);
			m_passingTime = 0.f;
		}
	}
	/*else
	{
		if (m_selectedItem)
			m_selectedItem->UnSelect();
		m_selectedItem = m_inventory->SelectItem(0);
		if (m_selectedItem)
			m_selectedItem->Select();
	}*/

	m_knifeCoolTime += dTime;
	if (m_knifeCoolTime > 30.f)
	{
		m_knifeCoolTime = 30.f;
		m_isKnifeReady = true;

		if (m_selectedItem == m_inventory->SelectItem(0))
		{
			if (InputManager::GetInstance()->m_Mouse.IsButtonHold(InputManager::GetInstance()->m_Mouse.rightButton))
			{
				if (m_passingTime < 1.f)
				{
					m_passingTime += dTime;
				}
				
				m_camera->SetFov(static_cast<int>(m_fov - m_passingTime * 30));

				if (m_passingTime >= 1.f)
				{
					m_passingTime = 1.f;
					if (InputManager::GetInstance()->m_Mouse.IsButtonDown(InputManager::GetInstance()->m_Mouse.leftButton))
					{
						UseSelectedItem();
						m_isKnifeAnimationPlaying = true;
						m_camera->SetFov(m_fov);
						m_knifeCoolTime = 0.f;
						m_isKnifeReady = false;
						m_passingTime = 0.f;
					}
				}
			}
			else
			{
		
				m_camera->SetFov(m_fov);
				m_passingTime = 0.f;
			}
		}
	}
}

void PlayerComponent::LateUpdate(float dTime)
{

}

void PlayerComponent::Render()
{

}

void PlayerComponent::Release()
{

}

void PlayerComponent::OnCollisionEnter(Collision* collision)
{
	if (collision->GetOwner()->GetComponent<EnemyComponent>())
	{
		m_hp = -1.f;
	}
}

void PlayerComponent::OnCollisionStay(Collision* collision)
{

}

void PlayerComponent::OnCollisionExit(Collision* collision)
{

}

void PlayerComponent::Interact(GameObject* _object)
{

}

void PlayerComponent::UseSelectedItem()
{
	if (m_selectedItem)
	{
		m_selectedItem->Act(m_pOwner);
	}
}

void PlayerComponent::SelectItem(const int& index)
{
	m_selectedItem = m_inventory->SelectItem(index);
}

void PlayerComponent::CheckInteractiveObject(float dTime)
{
	if (InputManager::GetInstance()->m_Keyboard.IsKeyHold('E'))
	{
		SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
		SimpleMath::Vector3 direction = m_pOwner->GetComponent<Transform>()->GetForward();
		origin += direction * 0.55;
		float maxDistance = 5.f;
		Collision* hit = nullptr;
		m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit);
		if (hit)
		{
			if (InteractiveObject* obj = hit->GetOwner()->GetComponent<InteractiveObject>())
			{


				m_isInteracting = true;
				if (m_isGameStarted)
				{
					obj->InteractAddTime(dTime);
				}
				else if (!m_isGameStarted && hit->GetOwner()->GetComponent<HeartChest>())
				{
					obj->InteractAddTime(dTime);
				}
			}
			else
			{
				m_isInteracting = false;
			}
		}
		else
		{
			m_isInteracting = false;
		}
	}
	else
	{
		m_isInteracting = false;
	}

	if (m_isBeforeInteracting != m_isInteracting)
	{
		// 뭔가 상호작용을 하고 있으면 손을 들어야 한다.
		if (m_isInteracting)
		{
			if (m_selectedItem)
				m_selectedItem->UnSelect();
			m_selectedItem = m_inventory->SelectItem(2);
			if (m_selectedItem)
				m_selectedItem->Select();
		}
		else
		{
			if (m_selectedItem)
				m_selectedItem->UnSelect();
			m_selectedItem = m_inventory->SelectItem(m_itemState);
			if (m_selectedItem)
				m_selectedItem->Select();
		}
		m_isBeforeInteracting = m_isInteracting;
	}

	// Test
// 	if (InputManager::GetInstance()->m_Keyboard.IsKeyHold('J'))
// 	{
// 		m_pOwner->GetComponent<Transform>()->SetPosition({ 0.f,0.f,0.f });
// 	}
}

void PlayerComponent::OnKnife()
{
	m_haveKnife = true;
	if (m_selectedItem)
		m_selectedItem->UnSelect();
	m_selectedItem = m_inventory->SelectItem(0);
	if (m_selectedItem)
		m_selectedItem->Select();
}

void PlayerComponent::OnHeart()
{

	m_haveHeart = true;
	if (m_selectedItem)
		m_selectedItem->UnSelect();
	m_selectedItem = m_inventory->SelectItem(1);
	if (m_selectedItem)
		m_selectedItem->Select();
}
