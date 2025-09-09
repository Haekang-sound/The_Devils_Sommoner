#include "pch.h"
#include "SphereCollision.h"
#include "Transform.h"
#include "GameObject.h"

SphereCollision::SphereCollision()
	: m_boundingSphere({ 0,0,0 }, { 0.5f }),
	m_transform(nullptr)
{

}

SphereCollision::~SphereCollision()
{

}

void SphereCollision::Start()
{
	m_transform = m_pOwner->GetComponent<Transform>();
	m_boundingSphere.Center = m_transform->GetPosition();
}

void SphereCollision::FixedUpdate(float dTime)
{

}

void SphereCollision::Update(float dTime)
{

}

void SphereCollision::LateUpdate(float dTime)
{
	m_boundingSphere.Center = m_transform->GetPosition();
	//std::cout << m_boundingSphere.Center.x << ", " << m_boundingSphere.Center.y << ", " << m_boundingSphere.Center.z << std::endl;
}

void SphereCollision::Render()
{
// 	m_renderer->DrawDebugingBoundingSphere({ m_boundingSphere.Center.x,
// 		m_boundingSphere.Center.y,
// 		m_boundingSphere.Center.z },
// 		m_boundingSphere.Radius,
// 		{1,0,0,1}
// 	);
}

void SphereCollision::Release()
{
	// Release

	// FinalRelease
	Super::Release();
}

const DirectX::BoundingSphere& SphereCollision::GetBoundingSphere()
{
	return m_boundingSphere;
}

void SphereCollision::SetCenter(const SimpleMath::Vector3& center)
{
	m_boundingSphere.Center = center;
}

void SphereCollision::SetRadius(const float& radius)
{
	m_boundingSphere.Radius = radius;
}
