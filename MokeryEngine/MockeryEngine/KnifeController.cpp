#include "pch.h"
#include "KnifeController.h"
#include "GameObject.h"
#include "Transform.h"
#include "InputManager.h"
#include "CameraComponent.h"
#include "EngineObjectManager.h"
#include "GameManager.h"
#include "SoundManager.h"

KnifeController::KnifeController()
	:isSet(true), m_state(KnifeSate::IDLE),
	m_camera(nullptr), m_transform(nullptr), isShoot(false)
{

}

void KnifeController::Start()
{
	m_transform = GetOwner()->GetComponent<Transform>();
	m_camera = GetOwner()->GetObjectManager()->GetOBjectsByComponent<CameraComponent>()->GetComponent<CameraComponent>();
}

void KnifeController::FixedUpdate(float dTime)
{
}

void KnifeController::Update(float dTime)
{
	switch (m_state)
	{
		case KnifeSate::IDLE:
		{
			
			m_camera->SetFov(90);
			// 1. 오브젝트를 그리지 않는다.
			// 2. 오브젝트가 충돌하지 않는다.
			// 3. 단검 타이머가 돌아가지 않는다.
		}

		break;
		case KnifeSate::AIM:
		{

			// 부모를 세팅한다.
			//GetOwner()->SetParentByName("Player");
			
			// fov를 조정한다.
			m_camera->SetFov(60);

			// 나이프를 손 위치에 세팅한다.
			SetKnifeTransform();

			// 플레이어의 포지션을 받아온다.(플레이어가 해제되기 전에 이루어져야한다.)
			m_parentPos = GetOwner()->GetParent()->GetComponent<Transform>()->GetPosition();
			m_parentRot = GetOwner()->GetParent()->GetComponent<Transform>()->GetRotation();

			// 부모의 포워드 벡터를 받아와야한다(그래야 부모가 바라보고있는 )
			m_parentfoward = GetOwner()->GetParent()->GetComponent<Transform>()->GetForward();
		}
		break;
		case KnifeSate::SHOOT:
		{
			m_camera->SetFov(60);
			//GetOwner()->SetParentByName("null");
			GetOwner()->SetParentByGameObject(nullptr);
			ShootKnife();
			
		}
		break;
		case KnifeSate::WAIT:

			break;
		default:
			break;
	}

	/// 기본상태
	// 1. 오브젝트가 그려지지 않는다.
	// 2. 오브젝트가 충돌하지 않는다.
	// 3. 단검 타이머가 돌아간다.	

	/// 조준상태
	// 투척, 기본으로 돌아갈 수 있다.
	if (InputManager::GetInstance()->m_Mouse.IsButtonDown(InputManager::GetInstance()->m_Mouse.rightButton))
	{
		if (m_state != KnifeSate::AIM)
		{
			m_state = KnifeSate::AIM;
			GetOwner()->SetParentByGameObject(GameManager::GetInstance()->GetPlayerObject());
		}
		else
		{
			m_state = KnifeSate::IDLE;
		}
	}

	/// 투척상태
	// 대기상태로 이어진다.
	// 1. 단검을 던진다.
	//		(단검이 충돌하면 대기상태가 된다.)
	//		(단검이 너무 멀어지면 대기상태가 된다.)
	// 2. 카메라 fov가 바뀐다
	if (InputManager::GetInstance()->m_Mouse.IsButtonDown(InputManager::GetInstance()->m_Mouse.leftButton) && m_state == KnifeSate::AIM)
	{
		m_transform->SetLocalPosition(m_parentPos);
		m_transform->SetLocalRotation(m_parentRot);

		m_state = KnifeSate::SHOOT;
	}
	// 조건이 맞으면 넘어간다

	/// 대기상태
	// 1. 오브젝트가 그려지지 않는다.
	// 2. 오브젝트가 충돌하지 않는다.
	// 3. 단검 타이머가 돌아간다.	
	// (타이머가 채워지면 기본상태로 돌아간다.)
	{
	}



}

void KnifeController::LateUpdate(float dTime)
{
}

void KnifeController::Render()
{
}

void KnifeController::Release()
{
}

// 카메라를 받아오자! 
void KnifeController::SetCamera(CameraComponent* camera)
{
	m_camera = camera;
}

void KnifeController::StateAim()
{

}

void KnifeController::StateIdle()
{

}

void KnifeController::StateShoot()
{

}

void KnifeController::ShootKnife()
{
	m_transform->TransportX(m_parentfoward.x * 0.2f);
	m_transform->TransportY(m_parentfoward.y * 0.2f);
	m_transform->TransportZ(m_parentfoward.z * 0.2f);
}

void KnifeController::SetKnifeTransform()
{
	// 카메라의 위치를 가져온다.
	// -> 부모로 두면 이미 가져옴
	m_transform->SetLocalPosition({ 1.5f,0.f, 3.f });
	m_transform->SetLocalRotation({ 90.f,0.f, 3.f });
	m_transform->SetLocalScale({ 0.2f, 0.2f, 1.0f });

	// (카메라의 위치는 부모의 위치 일까? )
}

