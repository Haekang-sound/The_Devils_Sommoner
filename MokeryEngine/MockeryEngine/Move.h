#pragma once
#include "Component.h"

class Transform;

/// <summary>
/// ������Ʈ�� �̵��� ����ϴ� ������Ʈ
/// �ٸ� ������Ʈ�ȿ��� ��Ʈ�ѷ� ������Ʈ�� �̵��Լ��� ȣ���Ѵ�.
/// �׷��� �̵��Ѵ�! 
/// </summary>
class Move : public Component
{
public:
	Move();

public:
	// IComponent��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

	// ��������

public:
	// �̵� 
	void TransportPositiveX(float dTime);	// 1. x�� �̵� +
	void TransportNegativeX(float dTime);	// 1. x�� �̵� -
	void TransportPositiveZ(float dTime);	// 2. z�� �̵� +
	void TransportNegativeZ(float dTime);	// 2. z�� �̵� -
	void TransportPositiveY(float dTime);	// 3. y�� �̵� +
	void TransportNegativeY(float dTime);	// 3. y�� �̵� -

	// ȸ��
	void RotatePositiveX(float radian);	// 1. x�� ȸ�� +
	void RotateNegativeX(float radian);	// 1. x�� ȸ�� -
	void RotatePositiveY(float radian);	// 2. y�� ȸ�� +
	void RotateNegativeY(float radian);	// 2. y�� ȸ�� -
	void RotatePositiveZ(float radian);	// 3. z�� ȸ�� +
	void RotateNegativeZ(float radian);	// 3. z�� ȸ�� -

protected:
	Transform* m_transform;
	SimpleMath::Vector3 m_pos;
	SimpleMath::Vector3 m_rot;
	float speed;


};