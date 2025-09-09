#pragma once
#include "Collision.h"

using namespace DirectX;

class Transform;
class ID3DRenderer;

/// <summary>
/// �� ������ �ѵ� ���߿� Collider��� ���� ��ü�� �ε簡 �� ������ �� �����̴�. ������ �����Ѵ�.
/// mk.1
/// 2024.01.31 - ���Լ�
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

	// start�������� owner GameObject�� Ʈ����������
	virtual void SetCenter(const SimpleMath::Vector3& center) override;
	void SetOrientation(const SimpleMath::Vector3& ori);
	void SetSize(const SimpleMath::Vector3& size);

	// ������ ���ش�.
	//void SetIsIntersect(const bool& isIntersect);
	//bool IsIntersect();

	//void SetTrigger(const bool& trigger);
	//bool IsTrigger();

	//CollisionState GetCollisionState();
	//void SetCollisionState(const CollisionState& state);


private:
	//BoundingBox m_boundingBox;
	BoundingOrientedBox m_boundingBox;

	// ���� ���ӿ�����Ʈ�� Transform�� �׳� �����ͼ� �������� �뵵
	Transform* m_transform;

	// ���ƴ���?
	bool m_isIntersect;

	bool m_isTrigger;

	ContainmentType m_containmentType;

	CollisionState m_collisionState;

};

