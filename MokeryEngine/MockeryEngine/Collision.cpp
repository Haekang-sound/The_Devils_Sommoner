#include "pch.h"
#include "Collision.h"

Collision::Collision()
	: m_collisionType(CollisionType::Static)
	, m_collisionWith(CollisionWith::All)
{

}

Collision::~Collision()
{

}

void Collision::Start()
{

}

void Collision::FixedUpdate(float dTime)
{

}

void Collision::Update(float dTime)
{

}

void Collision::LateUpdate(float dTime)
{

}

void Collision::Render()
{

}

void Collision::Release()
{
	m_detectedCollisionState.clear();
}

void Collision::SetIntersect(bool isIntersect)
{
	m_isIntersect = isIntersect;
}

bool Collision::GetIsIngersect()
{
	return m_isIntersect;
}

void Collision::SetTrigger(bool trigger)
{
	m_isTrigger = trigger;
}

bool Collision::GetIsTrigger()
{
	return m_isTrigger;
}

CollisionState Collision::GetCollisionState()
{
	return m_collisionState;
}

void Collision::SetCollisionState(const CollisionState& state)
{
	m_collisionState = state;
}

void Collision::AddCollisionDetected(Collision* collision, const CollisionState& state)
{
	// key가 있는지 여부를 확인한다.
	auto iter = m_detectedCollisionState.find(collision);
	if (iter != m_detectedCollisionState.end())
	{
		// 이미 있으면 반환
		return;
	}

	m_detectedCollisionState.insert({ collision,state });
}

const CollisionState& Collision::GetCollisionDetectedByCollisonPointerKey(Collision* collision)
{
	return m_detectedCollisionState[collision];
}

void Collision::SetCollisionDetectedState(Collision* collision, const CollisionState& state)
{
	m_detectedCollisionState[collision] = state;
}

const CollisionType& Collision::GetCollisionType()
{
	return m_collisionType;
}

void Collision::SetCollisionType(CollisionType type)
{
	m_collisionType = type;
}

void Collision::SetDebugCollisionColor(float r, float g, float b, float a)
{
	m_debugCollisionColor = { r,g,b,a };
}

void Collision::SetCollisionWith(const CollisionWith& with)
{
	m_collisionWith = with;
}

const CollisionWith& Collision::GetCollisionWith()
{
	return m_collisionWith;
}
