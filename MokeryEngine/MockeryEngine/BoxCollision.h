#pragma once
#include "Collision.h"

using namespace DirectX;

class Transform;
class ID3DRenderer;

/// <summary>
/// 좀 더럽긴 한데 나중에 Collider라는 상위 객체를 두든가 할 생각을 할 생각이다. 생각을 생각한다.
/// mk.1
/// 2024.01.31 - 강규석
/// </summary>
class BoxCollision : public Collision
{
	using Super = Collision;
public:
	BoxCollision();
	virtual ~BoxCollision();

public:
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

public:
	//const BoundingBox& GetBoundingBox();
	const BoundingOrientedBox& GetBoundingBox();

	// start과정에서 owner GameObject의 트랜스폼으로
	virtual void SetCenter(const SimpleMath::Vector3& center) override;
	void SetOrientation(const SimpleMath::Vector3& ori);
	void SetSize(const SimpleMath::Vector3& size);

	// 교차를 켜준다.
	//void SetIsIntersect(const bool& isIntersect);
	//bool IsIntersect();

	//void SetTrigger(const bool& trigger);
	//bool IsTrigger();

	//CollisionState GetCollisionState();
	//void SetCollisionState(const CollisionState& state);


private:
	//BoundingBox m_boundingBox;
	BoundingOrientedBox m_boundingBox;

	// 나의 게임오브젝트의 Transform을 그냥 가져와서 쓰기위한 용도
	Transform* m_transform;

	// 겹쳤는지?
	bool m_isIntersect;

	bool m_isTrigger;

	ContainmentType m_containmentType;

	CollisionState m_collisionState;

};

