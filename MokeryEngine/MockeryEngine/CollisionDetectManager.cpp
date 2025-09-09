#include "pch.h"
#include "CollisionDetectManager.h"
#include "Collision.h"
#include "BoxCollision.h"
#include "SphereCollision.h"
#include "GameObject.h"
#include "Transform.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"
#include "RigidBody.h"
#include "GameManager.h"
#include "CameraComponent.h"
#include "Transform.h"
//#include <limits>

CollisionDetectManager::CollisionDetectManager()
	: m_renderer(nullptr)
{

}

CollisionDetectManager::~CollisionDetectManager()
{

}

void CollisionDetectManager::Init()
{

}

void CollisionDetectManager::Update()
{
	//CheckCollisionDetection();
	//CheckCollisionDetection2();
	RenderMatrix44* proj = m_renderer->GetCameraProjection(0);

	SimpleMath::Matrix convertProj;
	memcpy(&convertProj, proj, sizeof(SimpleMath::Matrix));

	m_boundingFrustum = BoundingFrustum(convertProj);

	Transform* t = GameManager::GetInstance()->GetPlayerObject()->GetComponent<Transform>();
	
	m_boundingFrustum.Origin = t->GetPosition();
	m_boundingFrustum.Orientation = t->GetQuaternion();

	ObjectCulling();

	CheckCollisionDetection3();
}

void CollisionDetectManager::Finalize()
{
	m_boxes.clear();
	m_spheres.clear();
}

void CollisionDetectManager::AddBoxCollision(BoxCollision* collision)
{
	m_boxes.push_back(collision);
}

void CollisionDetectManager::AddSphereCollision(SphereCollision* collision)
{
	m_spheres.push_back(collision);
}

void CollisionDetectManager::CheckCollisionDetection()
{
	// 일단 모든 충돌체를 검사하는 방식으로 만들겠다. 
	for (int i = 0; i < m_boxes.size(); i++)
	{
		BoxCollision* c1 = m_boxes[i];
		// 중간에 삭제되는 오브젝트도 있을 수 있으니까 그건 일단 nullptr체크부터 하자
		if (!c1) continue;

		for (int j = i; j < m_boxes.size(); j++)
		{
			BoxCollision* c2 = m_boxes[j];
			if (!c2) continue;

			// 나와 나를 검사하면 안되니까
			if (c1 == c2) continue;

			ContainmentType containmentType = c1->GetBoundingBox().Contains(c2->GetBoundingBox());

			// 일단은 ConatainmentType에서 Intersect만 쓴다.
			if (containmentType == ContainmentType::INTERSECTS || containmentType == ContainmentType::CONTAINS)
			{
				c1->SetIntersect(true);

				if (c1->GetCollisionState() == CollisionState::None)
				{
					c1->SetCollisionState(CollisionState::Enter);
					//c1->OnCollisionEnter(c2);
					c1->GetOwner()->OnCollisionEnter(c2);
				}
				else if (c1->GetCollisionState() == CollisionState::Enter)
				{
					c1->SetCollisionState(CollisionState::Stay);
					//c1->OnCollisionStay(c2);
					c1->GetOwner()->OnCollisionStay(c2);
				}
				else if (c1->GetCollisionState() == CollisionState::Stay)
				{
					c1->GetOwner()->OnCollisionStay(c2);
				}

				// 밀어냄.. 사실 원위치 복귀?
				if (RigidBody* r1 = c1->GetOwner()->GetComponent<RigidBody>())
				{
					r1->OnCollision();
					r1->SetBeforePosition();
				}
				if (RigidBody* r2 = c2->GetOwner()->GetComponent<RigidBody>())
				{
					r2->OnCollision();
				}
			}
			else if (containmentType == ContainmentType::DISJOINT)
			{
				if (c1->GetCollisionState() == CollisionState::None)
					continue;

				c1->SetIntersect(false);
				if (c1->GetCollisionState() == CollisionState::Enter
					|| c1->GetCollisionState() == CollisionState::Stay
					)
				{
					c1->SetCollisionState(CollisionState::Exit);
					//c1->OnCollisionExit(c2);
					c1->GetOwner()->OnCollisionExit(c2);
				}
				else if (c1->GetCollisionState() == CollisionState::Exit)
				{
					c1->SetCollisionState(CollisionState::None);
				}
			}
		}
	}
}

void CollisionDetectManager::CheckCollisionDetection2()
{
	const int boxCount = m_boxes.size();
	const int sphereCount = m_spheres.size();
	const int collisionCount = boxCount + sphereCount;

	for (int i = 0; i < collisionCount; i++)
	{
		Collision* c1 = nullptr;
		if (i < boxCount)
		{
			c1 = m_boxes[i];
		}
		else
		{
			c1 = m_spheres[i - boxCount];
		}

		if (!c1) continue;

		for (int j = i; j < collisionCount; j++)
		{
			Collision* c2 = nullptr;
			if (j < boxCount)
			{
				c2 = m_boxes[j];
			}
			else
			{
				c2 = m_spheres[j - boxCount];
			}

			if (!c2) continue;

			if (c1 == c2) continue;

			ContainmentType containmentType;

			if (i < boxCount)
			{
				if (j < boxCount)
				{
					containmentType = ((BoxCollision*)c1)->GetBoundingBox().Contains(((BoxCollision*)c2)->GetBoundingBox());
				}
				else
				{
					containmentType = ((BoxCollision*)c1)->GetBoundingBox().Contains(((SphereCollision*)c2)->GetBoundingSphere());
				}
			}
			else
			{
				containmentType = ((SphereCollision*)c1)->GetBoundingSphere().Contains(((SphereCollision*)c2)->GetBoundingSphere());
			}

			if (containmentType == ContainmentType::INTERSECTS || containmentType == ContainmentType::CONTAINS)
			{
				c1->SetIntersect(true);

				// 부딪힌 collision과 해당 collision과의 state를 넣어준다.
				c1->AddCollisionDetected(c2, CollisionState::None);

				CollisionState c1ToC2State = c1->GetCollisionDetectedByCollisonPointerKey(c2);

				if (c1ToC2State == CollisionState::None)
				{
					c1->SetCollisionDetectedState(c2, CollisionState::Enter);
					//c1->OnCollisionEnter(c2);
					c1->GetOwner()->OnCollisionEnter(c2);
				}
				else if (c1ToC2State == CollisionState::Enter)
				{
					c1->SetCollisionDetectedState(c2, CollisionState::Stay);
					//c1->OnCollisionStay(c2);
					c1->GetOwner()->OnCollisionStay(c2);
				}
				else if (c1ToC2State == CollisionState::Stay)
				{
					c1->GetOwner()->OnCollisionStay(c2);
				}

				// 밀어냄.. 사실 원위치 복귀?
				if (RigidBody* r1 = c1->GetOwner()->GetComponent<RigidBody>())
				{
					r1->OnCollision();
					r1->SetBeforePosition();
				}
				if (RigidBody* r2 = c2->GetOwner()->GetComponent<RigidBody>())
				{
					r2->OnCollision();
				}
			}
			else if (containmentType == ContainmentType::DISJOINT)
			{
				c1->AddCollisionDetected(c2, CollisionState::None);

				CollisionState c1ToC2State = c1->GetCollisionDetectedByCollisonPointerKey(c2);

				if (c1ToC2State == CollisionState::None)
					continue;

				c1->SetIntersect(false);

				if (c1ToC2State == CollisionState::Enter
					|| c1ToC2State == CollisionState::Stay
					)
				{
					c1->SetCollisionDetectedState(c2, CollisionState::Exit);
					c1->GetOwner()->OnCollisionExit(c2);
				}
				else if (c1ToC2State == CollisionState::Exit)
				{
					c1->SetCollisionDetectedState(c2, CollisionState::None);
				}
			}
		}
	}
}

void CollisionDetectManager::CheckCollisionDetection3()
{
	const int boxCount = m_boxes.size();
	const int sphereCount = m_spheres.size();
	const int collisionCount = boxCount + sphereCount;

	for (int i = 0; i < collisionCount; i++)
	{
		Collision* c1 = nullptr;
		if (i < boxCount)
		{
			c1 = m_boxes[i];
		}
		else
		{
			c1 = m_spheres[i - boxCount];
		}

		if (!c1) continue;
		if (c1->GetCollisionWith() == CollisionWith::Nothing) continue;
		// 정적일 경우 다른 충돌체와 처리를 일단은 안해준다.
		if (c1->GetCollisionType() == CollisionType::Static) continue;

		//for (int j = i; j < collisionCount; j++)
		for (int j = 0; j < collisionCount; j++)
		{
			Collision* c2 = nullptr;
			if (j < boxCount)
			{
				c2 = m_boxes[j];
			}
			else
			{
				c2 = m_spheres[j - boxCount];
			}

			if (!c2) continue;
			if (c2->GetCollisionWith() == CollisionWith::Nothing) continue;

			if (c1 == c2) continue;

			ContainmentType containmentType;

			if (i < boxCount)
			{
				if (j < boxCount)
				{
					containmentType = ((BoxCollision*)c1)->GetBoundingBox().Contains(((BoxCollision*)c2)->GetBoundingBox());
				}
				else
				{
					containmentType = ((BoxCollision*)c1)->GetBoundingBox().Contains(((SphereCollision*)c2)->GetBoundingSphere());
				}
			}
			else
			{
				containmentType = ((SphereCollision*)c1)->GetBoundingSphere().Contains(((SphereCollision*)c2)->GetBoundingSphere());
			}

			if (containmentType == ContainmentType::INTERSECTS || containmentType == ContainmentType::CONTAINS)
			{
				c1->SetIntersect(true);
				c2->SetIntersect(true);

				// 부딪힌 collision과 해당 collision과의 state를 넣어준다.
				c1->AddCollisionDetected(c2, CollisionState::None);
				c2->AddCollisionDetected(c1, CollisionState::None);

				CollisionState c1ToC2State = c1->GetCollisionDetectedByCollisonPointerKey(c2);

				if (c1ToC2State == CollisionState::None)
				{
					c1->SetCollisionDetectedState(c2, CollisionState::Enter);
					c2->SetCollisionDetectedState(c1, CollisionState::Enter);
					//c1->OnCollisionEnter(c2);
					c1->GetOwner()->OnCollisionEnter(c2);
					c2->GetOwner()->OnCollisionEnter(c1);
				}
				else if (c1ToC2State == CollisionState::Enter)
				{
					c1->SetCollisionDetectedState(c2, CollisionState::Stay);
					c2->SetCollisionDetectedState(c1, CollisionState::Stay);
					//c1->OnCollisionStay(c2);
					c1->GetOwner()->OnCollisionStay(c2);
					c2->GetOwner()->OnCollisionStay(c1);
				}
				else if (c1ToC2State == CollisionState::Stay)
				{
					c1->GetOwner()->OnCollisionStay(c2);
					c2->GetOwner()->OnCollisionStay(c1);
				}

				// 밀어냄.. 사실 원위치 복귀?
				if (c1->GetCollisionWith() != CollisionWith::OnlyRay
					&& c2->GetCollisionWith() != CollisionWith::OnlyRay
					)
				{
					if (RigidBody* r1 = c1->GetOwner()->GetComponent<RigidBody>())
					{
						r1->OnCollision();
						r1->SetBeforePosition();
						//std::cout << "Set before position" << std::endl;
						r1->GetOwner()->GetComponent<Transform>()->UpdateTransform();
					}
					if (RigidBody* r2 = c2->GetOwner()->GetComponent<RigidBody>())
					{
						r2->OnCollision();
						//r2->SetBeforePosition();
						//std::cout << "Set before position" << std::endl;
						r2->GetOwner()->GetComponent<Transform>()->UpdateTransform();
					}
				}
			}
			else if (containmentType == ContainmentType::DISJOINT)
			{
				c1->AddCollisionDetected(c2, CollisionState::None);
				c2->AddCollisionDetected(c1, CollisionState::None);

				CollisionState c1ToC2State = c1->GetCollisionDetectedByCollisonPointerKey(c2);

				if (c1ToC2State == CollisionState::None)
					continue;

				c1->SetIntersect(false);
				c2->SetIntersect(false);

				if (c1ToC2State == CollisionState::Enter
					|| c1ToC2State == CollisionState::Stay
					)
				{
					c1->SetCollisionDetectedState(c2, CollisionState::Exit);
					c2->SetCollisionDetectedState(c1, CollisionState::Exit);

					c1->GetOwner()->OnCollisionExit(c2);
					c2->GetOwner()->OnCollisionExit(c1);
				}
				else if (c1ToC2State == CollisionState::Exit)
				{
					c1->SetCollisionDetectedState(c2, CollisionState::None);
					c2->SetCollisionDetectedState(c1, CollisionState::None);
				}
			}
		}
	}
}

Collision* CollisionDetectManager::CheckRay(const SimpleMath::Vector3& origin, const SimpleMath::Vector3& direction, float distance)
{
	Collision* outCollision = nullptr;
	//float distance = 3.4e+38;
	float compDist = 0.f;

	const int boxCount = m_boxes.size();
	const int sphereCount = m_spheres.size();

	//SimpleMath::Vector3 dir = direction;
	//dir.Normalize();

	SimpleMath::Ray ray(origin, direction);

	if (!DirectX::Internal::XMVector3IsUnit(direction))
	{
		return nullptr;
	}

	for (int i = 0; i < boxCount; i++)
	{
		
		//bool isIntersect = m_boxes[i]->GetBoundingBox().Intersects(origin, direction, compDist);
		//bool isIntersect = ray.Intersects(m_boxes[i]->GetBoundingBox(), compDist);

		bool isIntersect = m_boxes[i]->GetBoundingBox().Intersects(origin, direction, compDist);
		
		if (!isIntersect) continue;

		if (compDist < distance)
		{
			outCollision = m_boxes[i];
			distance = compDist;
		}
	}

	for (int i = 0; i < sphereCount; i++)
	{
		//bool isIntersect = m_spheres[i]->GetBoundingSphere().Intersects(origin, direction, compDist);
		bool isIntersect = ray.Intersects(m_spheres[i]->GetBoundingSphere(), compDist);

		if (!isIntersect) continue;

		if (compDist < distance)
		{
			outCollision = m_spheres[i];
			distance = compDist;
		}
	}

	if (!outCollision)
		return nullptr;

	return outCollision;
}

Collision* CollisionDetectManager::CheckRay(const SimpleMath::Vector3& origin, const SimpleMath::Vector3& direction, float distance, std::function<bool(Collision*)> func)
{
	Collision* outCollision = nullptr;
	//float distance = 3.4e+38;
	float compDist = 0.f;

	const int boxCount = m_boxes.size();
	const int sphereCount = m_spheres.size();

	//SimpleMath::Vector3 dir = direction;
	//dir.Normalize();

	SimpleMath::Ray ray(origin, direction);

	for (int i = 0; i < boxCount; i++)
	{

		//bool isIntersect = m_boxes[i]->GetBoundingBox().Intersects(origin, direction, compDist);
		//bool isIntersect = ray.Intersects(m_boxes[i]->GetBoundingBox(), compDist);
		bool isIntersect = m_boxes[i]->GetBoundingBox().Intersects(origin, direction, compDist);
		if (!isIntersect) continue;

		if (!func(m_boxes[i])) continue;

		if (compDist < distance)
		{
			outCollision = m_boxes[i];
			distance = compDist;
		}
	}

	for (int i = 0; i < sphereCount; i++)
	{
		//bool isIntersect = m_spheres[i]->GetBoundingSphere().Intersects(origin, direction, compDist);
		bool isIntersect = ray.Intersects(m_spheres[i]->GetBoundingSphere(), compDist);
		if (!isIntersect) continue;

		if (!func(m_spheres[i])) continue;

		if (compDist < distance)
		{
			outCollision = m_spheres[i];
			distance = compDist;
		}
	}

	if (!outCollision)
		return nullptr;

	return outCollision;
}

void CollisionDetectManager::ObjectCulling()
{
	//m_boundingFrustum

	const int boxCount = m_boxes.size();
	const int sphereCount = m_spheres.size();

	for (int i = 0; i < boxCount; i++)
	{
		ContainmentType type = m_boundingFrustum.Contains(m_boxes[i]->GetBoundingBox());

		if (type == ContainmentType::DISJOINT)
		{
			m_boxes[i]->GetOwner()->SetIsDrawRecursively(false);
		}
		else
		{
			if (m_boxes[i]->GetOwner()->GetIsActive() == true)
				m_boxes[i]->GetOwner()->SetIsDrawRecursively(true);
		}
	}

	for (int i = 0; i < sphereCount; i++)
	{
		ContainmentType type = m_boundingFrustum.Contains(m_spheres[i]->GetBoundingSphere());

		if (type == ContainmentType::DISJOINT)
		{
			m_spheres[i]->GetOwner()->SetIsDrawRecursively(false);
		}
		else
		{
			if(m_spheres[i]->GetOwner()->GetIsActive() == true)
				m_spheres[i]->GetOwner()->SetIsDrawRecursively(true);
		}
	}
}

void CollisionDetectManager::SetRenderer(ID3DRenderer* renderer)
{
	m_renderer = renderer;
}
