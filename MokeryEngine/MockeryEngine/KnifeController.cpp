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
			// 1. ������Ʈ�� �׸��� �ʴ´�.
			// 2. ������Ʈ�� �浹���� �ʴ´�.
			// 3. �ܰ� Ÿ�̸Ӱ� ���ư��� �ʴ´�.
		}

		break;
		case KnifeSate::AIM:
		{

			// �θ� �����Ѵ�.
			//GetOwner()->SetParentByName("Player");
			
			// fov�� �����Ѵ�.
			m_camera->SetFov(60);

			// �������� �� ��ġ�� �����Ѵ�.
			SetKnifeTransform();

			// �÷��̾��� �������� �޾ƿ´�.(�÷��̾ �����Ǳ� ���� �̷�������Ѵ�.)
			m_parentPos = GetOwner()->GetParent()->GetComponent<Transform>()->GetPosition();
			m_parentRot = GetOwner()->GetParent()->GetComponent<Transform>()->GetRotation();

			// �θ��� ������ ���͸� �޾ƿ;��Ѵ�(�׷��� �θ� �ٶ󺸰��ִ� )
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

	/// �⺻����
	// 1. ������Ʈ�� �׷����� �ʴ´�.
	// 2. ������Ʈ�� �浹���� �ʴ´�.
	// 3. �ܰ� Ÿ�̸Ӱ� ���ư���.	

	/// ���ػ���
	// ��ô, �⺻���� ���ư� �� �ִ�.
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

	/// ��ô����
	// �����·� �̾�����.
	// 1. �ܰ��� ������.
	//		(�ܰ��� �浹�ϸ� �����°� �ȴ�.)
	//		(�ܰ��� �ʹ� �־����� �����°� �ȴ�.)
	// 2. ī�޶� fov�� �ٲ��
	if (InputManager::GetInstance()->m_Mouse.IsButtonDown(InputManager::GetInstance()->m_Mouse.leftButton) && m_state == KnifeSate::AIM)
	{
		m_transform->SetLocalPosition(m_parentPos);
		m_transform->SetLocalRotation(m_parentRot);

		m_state = KnifeSate::SHOOT;
	}
	// ������ ������ �Ѿ��

	/// ������
	// 1. ������Ʈ�� �׷����� �ʴ´�.
	// 2. ������Ʈ�� �浹���� �ʴ´�.
	// 3. �ܰ� Ÿ�̸Ӱ� ���ư���.	
	// (Ÿ�̸Ӱ� ä������ �⺻���·� ���ư���.)
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

// ī�޶� �޾ƿ���! 
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
	// ī�޶��� ��ġ�� �����´�.
	// -> �θ�� �θ� �̹� ������
	m_transform->SetLocalPosition({ 1.5f,0.f, 3.f });
	m_transform->SetLocalRotation({ 90.f,0.f, 3.f });
	m_transform->SetLocalScale({ 0.2f, 0.2f, 1.0f });

	// (ī�޶��� ��ġ�� �θ��� ��ġ �ϱ�? )
}

