#include "pch.h"
#include "BoxCollision.h"
#include "GameObject.h"
#include "Transform.h"

//SimpleMath::Quaternion ToQuaternion(float roll, float pitch, float yaw) // roll (x), pitch (y), yaw (z), angles are in radians
SimpleMath::Quaternion ToQuaternion(SimpleMath::Vector3 e) // roll (x), pitch (y), yaw (z), angles are in radians
{
	// Abbreviations for the various angular functions

	float cy = cos(e.z * 0.5);
	float sy = sin(e.z * 0.5);
	float cp = cos(e.y * 0.5);
	float sp = sin(e.y * 0.5);
	float cr = cos(e.x * 0.5);
	float sr = sin(e.x * 0.5);

	SimpleMath::Quaternion q;
	q.w = cy * cp * cr + sy * sp * sr;
	q.x = cy * cp * sr - sy * sp * cr;
	q.y = sy * cp * sr + cy * sp * cr;
	q.z = sy * cp * cr - cy * sp * sr;

	return q;
}

BoxCollision::BoxCollision()
	: m_boundingBox({ 0.f,0.f,0.f }, { 2.f,2.f,2.f }, { 0.f,1.f,0.f,0.f }),
	m_transform(nullptr),
	m_isIntersect(false),
	m_isTrigger(false),
	m_containmentType(),
	m_collisionState(CollisionState::None)
{
	m_debugCollisionColor = { 1,1,1,1 };
}

BoxCollision::~BoxCollision()
{

}

void BoxCollision::Start()
{
	m_transform = m_pOwner->GetComponent<Transform>();
	m_boundingBox.Center = m_transform->GetPosition();
}

void BoxCollision::Update(float dTime)
{
	SimpleMath::Quaternion q = ToQuaternion(m_transform->GetRotation());
	m_boundingBox.Orientation = q;

	// 오해강
	//  어차피 트랜스폼 갖고 있으니까 여기서 하면 안돼?
	//SetSize(m_transform->GetLocalScale());
}

void BoxCollision::LateUpdate(float dTime)
{
	
}

void BoxCollision::Render()
{
	SimpleMath::Quaternion q = ToQuaternion(m_transform->GetRotation());
	m_boundingBox.Orientation = q;

	m_boundingBox.Center = m_transform->GetPosition();
	//m_renderer->DrawDebugingBoundingBox({ m_boundingBox.Center.x, m_boundingBox.Center.y, m_boundingBox.Center.z },
	//	{ m_boundingBox.Extents.x, m_boundingBox.Extents.y, m_boundingBox.Extents.z },
	//	{ q.x,q.y,q.z,q.w }, m_debugCollisionColor
	//);
}

void BoxCollision::Release()
{
	// Release

	// FinalRelease
	Super::Release();
}

const DirectX::BoundingOrientedBox& BoxCollision::GetBoundingBox()
{
	return m_boundingBox;
}

void BoxCollision::SetCenter(const SimpleMath::Vector3& center)
{
	//m_center = center;
	m_boundingBox.Center = center;
}

void BoxCollision::SetOrientation(const SimpleMath::Vector3& ori)
{
	SimpleMath::Quaternion q = ToQuaternion(ori);
	m_boundingBox.Orientation = q;
}

void BoxCollision::SetSize(const SimpleMath::Vector3& size)
{
	//m_size = size;
	m_boundingBox.Extents = size;
}

//void BoxCollision::SetIsIntersect(const bool& isIntersect)
//{
//	m_isIntersect = isIntersect;
//}
//
//bool BoxCollision::IsIntersect()
//{
//	return m_isIntersect;
//}
//
//void BoxCollision::SetTrigger(const bool& trigger)
//{
//	m_isTrigger = trigger;
//}
//
//bool BoxCollision::IsTrigger()
//{
//	return m_isTrigger;
//}
//
//CollisionState BoxCollision::GetCollisionState()
//{
//	return m_collisionState;
//}
//
//void BoxCollision::SetCollisionState(const CollisionState& state)
//{
//	m_collisionState = state;
//}

void BoxCollision::FixedUpdate(float dTime)
{

}
