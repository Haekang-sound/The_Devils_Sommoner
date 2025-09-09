#include "pch.h"
#include "Move.h"
#include "GameObject.h"
#include "Transform.h"


#ifdef _DEBUG
	#include <iostream>
#endif

Move::Move()
	:speed(1.f), m_transform(nullptr)
{

}

void Move::Start()
{
    // ��Ʈ�ѷ��� ���Ե� ������Ʈ���� transform�� �����´�.
	m_transform = GetOwner()->GetComponent<Transform>();

    // ��Ʈ�ѷ��� �⺻pos�� rot�� Ʈ�������� �����ش�.
	m_pos = m_transform->GetPosition();
    m_rot = m_transform->GetRotation();
}

void Move::Update(float dTime)
{
#ifdef _DEBUG
	//SimpleMath::Vector3 pos = m_pOwner->GetComponent<Transform>()->GetPosition();
	m_pos = m_transform->GetPosition();
	//std::cout << "pos : " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

	//std::cout << m_rot.x << std::endl;
	//SimpleMath::Vector3 pos = m_pOwner->GetComponent<Transform>()->GetPosition();
	//std::cout << "pos : " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
#endif // _DEBUG

}

void Move::LateUpdate(float dTime)
{
	SimpleMath::Vector3 pos = m_pOwner->GetComponent<Transform>()->GetPosition();
	//std::cout << GetOwner()->GetName() << ", pos : " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
	//std::cout << "pos : " << m_pos.x << ", " << m_pos.y << ", " << m_pos.z << std::endl;
}

void Move::Render()
{
}

void Move::Release()
{
}

// �̵��Լ�
void Move::TransportPositiveX(float dTime)
{
	SimpleMath::Vector3 _pos = m_transform->GetLocalPosition();
	_pos.x += dTime * speed;
    m_transform->SetPosition(_pos);
}

void Move::TransportNegativeX(float dTime)
{
	SimpleMath::Vector3 _pos = m_transform->GetLocalPosition();
	_pos.x -= dTime * speed;
	m_transform->SetPosition(_pos);
}

void Move::TransportPositiveZ(float dTime)
{
	SimpleMath::Vector3 _pos = m_transform->GetLocalPosition();
	_pos.z += dTime * speed;
	m_transform->SetPosition(_pos);
}

void Move::TransportNegativeZ(float dTime)
{
	SimpleMath::Vector3 _pos = m_transform->GetLocalPosition();
	_pos.z -= dTime * speed;
	m_transform->SetPosition(_pos);
}

void Move::TransportPositiveY(float dTime)
{
	SimpleMath::Vector3 _pos = m_transform->GetLocalPosition();
	_pos.y += dTime * speed;
	m_transform->SetPosition(_pos);
}

void Move::TransportNegativeY(float dTime)
{
	SimpleMath::Vector3 _pos = m_transform->GetLocalPosition();
	_pos.y -= dTime * speed;
	m_transform->SetPosition(_pos);
}

// ȸ���Լ�
void Move::RotatePositiveX(float radian)
{
	SimpleMath::Vector3 _rot = m_transform->GetLocalRotation();
	_rot.x += radian;

	if (m_rot.x > 360.f)
	{
		m_rot.x = 0.f;
	}

	m_transform->SetRotation(_rot);
} 

void Move::RotateNegativeX(float radian)
{
	m_rot.x -= radian;
	if (m_rot.x < -360.f)
	{
		m_rot.x = 0.f;
	}
	m_transform->SetRotation(m_rot);

	//std::cout << "m_rot.x : " << m_rot.x << std::endl;
}

void Move::RotatePositiveY(float radian)
{
	SimpleMath::Vector3 _rot = m_transform->GetLocalRotation();
	_rot.y += radian;

	if (m_rot.y > 360.f)
	{
		m_rot.y = 0.f;
	}

	m_transform->SetRotation(_rot);
}

void Move::RotateNegativeY(float radian)
{
	m_rot.y -= radian;
	if (m_rot.y < -360.f)
	{
		m_rot.y = 0.f;
	}
	m_transform->SetRotation(m_rot);
	//std::cout << "m_rot.y : " << m_rot.y << std::endl;
}

void Move::RotatePositiveZ(float radian)
{
	m_rot.z += radian;
	if (m_rot.z > 360.f)
	{
		m_rot.z = 0.f;
	}
	m_transform->SetRotation(m_rot);
	//std::cout << "m_rot.z : " << m_rot.z << std::endl;
}

void Move::RotateNegativeZ(float radian)
{
	m_rot.z -= radian;
	if (m_rot.z < -360.f)
	{
		m_rot.z = 0.f;
	}
	m_transform->SetRotation(m_rot);
	//std::cout << "m_rot.z : " << m_rot.z << std::endl;
}

void Move::FixedUpdate(float dTime)
{
}
