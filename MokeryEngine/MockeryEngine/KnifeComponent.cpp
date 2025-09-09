#include "pch.h"
#include "KnifeComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "Collision.h"
#include "EnemyComponent.h"
#include "Blind.h"
#include "Chaser.h"
#include "Utils.h"

KnifeComponent::KnifeComponent()
	: m_transform(nullptr)
	, m_state(KnifeObjectState::Idle)
	, m_speed(0.f)
{

}

KnifeComponent::~KnifeComponent()
{

}

void KnifeComponent::OnCollisionEnter(Collision* collision)
{
	// 아이들일 상태에는 아무 처리도 해주지 않는다.
	if (m_state == KnifeObjectState::Idle)
		return;

	// 일단은 chaser만 처리하겠음
	if (EnemyComponent* chaser = collision->GetOwner()->GetComponent<EnemyComponent>())
	{
		m_state = KnifeObjectState::Idle;

		// 여기서 몬스터한테 표식을 남겨야 한다.
		collision->GetOwner()->GetComponent<EnemyComponent>()->SetEnemyStun();

		// 그리고 절대적인 월드 포지션으로 이동한다. 그냥 계속 이 오브젝트를 돌려 쓸 것이기 때문이다. 
		m_transform->SetPosition({ 0.f, -100.f, 0.f });
	}

	// 여기서 무엇을 충돌한든 처리를 해주어야 한다. 
	if (collision)
	{
		m_state = KnifeObjectState::Idle;

		// 여기서 몬스터한테 표식을 남겨야 한다.
		//collision->GetOwner()->GetComponent<EnemyComponent>()->SetEnemyState();

		// 그리고 절대적인 월드 포지션으로 이동한다. 그냥 계속 이 오브젝트를 돌려 쓸 것이기 때문이다. 
		m_transform->SetPosition({ 0.f, -100.f, 0.f });
	}
}

void KnifeComponent::Start()
{
	m_transform = m_pOwner->GetComponent<Transform>();
}

void KnifeComponent::FixedUpdate(float dTime)
{

}

void KnifeComponent::Update(float dTime)
{
	switch (m_state)
	{
		case KnifeObjectState::Idle:
		{

		}
		break;
		case KnifeObjectState::Shoot:
		{
			SimpleMath::Vector3 newPos = m_transform->GetPosition();
			newPos += m_dir * m_speed * dTime;
			m_transform->SetPosition(newPos);
		}
		break;
		default:
			break;
	}
}

void KnifeComponent::LateUpdate(float dTime)
{

}

void KnifeComponent::Render()
{
// 	SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
// 	SimpleMath::Vector3 direction = m_dir;
// 	SimpleMath::Vector3 direction2 = m_pOwner->GetComponent<Transform>()->GetForward();;
// 
// 	m_renderer->DrawDebugingRay(
// 		{ origin.x, origin.y, origin.z, 1.f },
// 		{ direction.x, direction.y, direction.z, 1.f },
// 		{ 1.f,0.f,0.f,1.f },
// 		false
// 	);
// 
// 	m_renderer->DrawDebugingRay(
// 		{ origin.x, origin.y, origin.z, 1.f },
// 		{ direction2.x, direction2.y, direction2.z, 1.f },
// 		{ 0.f,0.f,1.f,1.f },
// 		false
// 	);

}

void KnifeComponent::Release()
{

}

void KnifeComponent::Shoot(const SimpleMath::Vector3& position, const SimpleMath::Vector3& direction, const SimpleMath::Vector3& rotation)
{
	m_transform->SetPosition(position);

	m_dir = direction;
	m_state = KnifeObjectState::Shoot;

	m_dir.Normalize();

	//m_transform->SetRotation({0.f, rotation.y, 0.f});
	m_transform->SetRotation(rotation);
}

void KnifeComponent::SetDirection(const SimpleMath::Vector3& direction)
{

}

void KnifeComponent::SetSpeed(const float& speed)
{
	m_speed = speed;
}

void KnifeComponent::SetState(const KnifeObjectState& state)
{
	m_state = state;
}
