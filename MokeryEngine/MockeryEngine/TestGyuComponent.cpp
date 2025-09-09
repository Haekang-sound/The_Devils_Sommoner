#include "pch.h"
#include "TestGyuComponent.h"
#include "Collision.h"
#include "GameObject.h"
#include "InputManager.h"
#include "RayComponent.h"
#include "Transform.h"
#include "Collision.h"

//#include <iostream>
TestGyuComponent::TestGyuComponent()
{

}

TestGyuComponent::~TestGyuComponent()
{

}

void TestGyuComponent::Start()
{

}

void TestGyuComponent::FixedUpdate(float dTime)
{

}

void TestGyuComponent::Update(float dTime)
{
	//SimpleMath::Vector3 rot = m_pOwner->GetComponent<Transform>()->GetRotation();
	//rot.z += 0.3f * dTime;
	//if (rot.x >= 180.f)
		//rot.x = 180.f;
	//m_pOwner->GetComponent<Transform>()->SetRotation(rot);
	//if (InputManager::GetInstance()->m_Keyboard.IsKeydown('P'))
	//{
	//	SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
	//	origin.x += 2.f;
	//	SimpleMath::Vector3 direction = SimpleMath::Vector3(10.f, 0.f, 0.f);
	//	float maxDistance = 5.f;
	//	Collision* hit = nullptr;

	//	//direction.Normalize();

	//	m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit);
	//	if (hit)
	//	{
	//		//std::cout << hit->GetOwner()->GetName() << std::endl;
	//	}
	//}
	//if (InputManager::GetInstance()->m_Keyboard.IsKeydown('O'))
	//{
	//	SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
	//	origin.x -= 2.f;
	//	SimpleMath::Vector3 direction = SimpleMath::Vector3(-1.f, 0.f, 0.f);
	//	float maxDistance = 5.f;
	//	Collision* hit = nullptr;

	//	direction.Normalize();

	//	m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit, [](Collision* col) {if (col->GetOwner()->GetName() == "col3") return true; });
	//	if (hit)
	//	{
	//		//std::cout << hit->GetOwner()->GetName() << std::endl;
	//	}
	//}

// 	if (InputManager::GetInstance()->m_Keyboard.IsKeyHold('O'))
// 	{
// 		SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
// 		origin.x -= 10.f * dTime;
// 		m_pOwner->GetComponent<Transform>()->SetPosition(origin);
// 	}
// 	else if (InputManager::GetInstance()->m_Keyboard.IsKeyHold('P'))
// 	{
// 		SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
// 		origin.x += 10.f * dTime;
// 		m_pOwner->GetComponent<Transform>()->SetPosition(origin);
// 	}
// 	{
// 		SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
// 		SimpleMath::Vector3 direction = m_pOwner->GetComponent<Transform>()->GetForward();
// 		direction.Normalize();
// 		m_renderer->DrawDebugingRay(
// 			{ origin.x, origin.y, origin.z, 1.f },
// 			{ direction.x, direction.y, direction.z, 1.f },
// 			{ 0,0,1,1 }, true);
// 	}
}

void TestGyuComponent::LateUpdate(float dTime)
{

}

void TestGyuComponent::Render()
{

}

void TestGyuComponent::Release()
{

}

void TestGyuComponent::OnCollisionEnter(Collision* collision)
{
	//std::cout << "OnCollisionEnter : " << collision->GetOwner()->GetName()<<std::endl;
}

void TestGyuComponent::OnCollisionStay(Collision* collision)
{
	//std::cout << "OnCollisionStay: " << collision->GetOwner()->GetName() << std::endl;
}

void TestGyuComponent::OnCollisionExit(Collision* collision)
{
	//std::cout << "OnCollisionExit: " << collision->GetOwner()->GetName() << std::endl;
}
