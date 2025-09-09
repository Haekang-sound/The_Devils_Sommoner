#include "pch.h"
#include "RayComponent.h"
#include "CollisionDetectManager.h"

RayComponent::RayComponent()
{

}

RayComponent::~RayComponent()
{

}

void RayComponent::Start()
{

}

void RayComponent::FixedUpdate(float dTime)
{

}

void RayComponent::Update(float dTime)
{

}

void RayComponent::LateUpdate(float dTime)
{

}

void RayComponent::Render()
{

}

void RayComponent::Release()
{

}

void RayComponent::SetCollisionDetectManager(CollisionDetectManager* manager)
{
	m_collisionDetectManager = manager;
}

void RayComponent::Ray(const SimpleMath::Vector3& origin, SimpleMath::Vector3 direction, float distance, Collision** outCollision)
{
	direction.Normalize();
	*outCollision = m_collisionDetectManager->CheckRay(origin, direction, distance);
}

void RayComponent::Ray(const SimpleMath::Vector3& origin, SimpleMath::Vector3 direction, float distance, Collision** outCollision, std::function<bool(Collision*)> func)
{
	direction.Normalize();
	*outCollision = m_collisionDetectManager->CheckRay(origin, direction, distance, func);
}
