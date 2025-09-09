#include "pch.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "Transform.h"

#include "BoxCollision.h"
#include "SphereCollision.h"

RigidBody::RigidBody()
{

}

RigidBody::~RigidBody()
{

}

void RigidBody::Start()
{
	m_beforePosition = m_pOwner->GetComponent<Transform>()->GetPosition();
	m_beforeRotation = m_pOwner->GetComponent<Transform>()->GetRotation();
}

void RigidBody::Update(float dTime)
{
	
}

void RigidBody::LateUpdate(float dTime)
{
	//m_beforePosition = m_pOwner->GetComponent<Transform>()->GetPosition();
}

void RigidBody::FixedUpdate(float dTime)
{

}

void RigidBody::Render()
{

}

void RigidBody::Release()
{

}

void RigidBody::OnTrigger()
{
	
}

void RigidBody::OnCollision()
{
	//std::cout << m_beforePosition.x << std::endl;
	
	// 뭔가 충돌 처리를 해준다.
	m_pOwner->GetComponent<Transform>()->SetPosition(m_beforePosition);
	//m_pOwner->GetComponent<Transform>()->SetRotation(m_beforeRotation);

	// TEMP : 아직은 BoxCollision 이다 . 2024.02.08 - 강규석
	if (BoxCollision* c = m_pOwner->GetComponent<BoxCollision>())
	{
		c->SetCenter(m_beforePosition);
		//c->SetOrientation(m_beforeRotation);
	}
	if (SphereCollision* c = m_pOwner->GetComponent<SphereCollision>())
	{
		c->SetCenter(m_beforePosition);
	}
}

void RigidBody::SetBeforePosition()
{
	m_beforePosition = m_pOwner->GetComponent<Transform>()->GetPosition();
	//m_beforeRotation = m_pOwner->GetComponent<Transform>()->GetRotation();
	//m_pOwner->GetComponent<Transform>()->SetPosition(m_beforePosition);
}

DirectX::SimpleMath::Vector3 RigidBody::GetBeforePosition()
{
	return m_beforePosition;
}
