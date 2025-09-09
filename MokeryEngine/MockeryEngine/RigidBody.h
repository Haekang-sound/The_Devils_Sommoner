#pragma once
#include "Component.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"

using namespace DirectX;

/// <summary>
/// �浹 ó���� ���� ������Ʈ
/// ��� �ָ��� �������̴� 
/// 2024.02.01 - ���Լ�
/// </summary>
class RigidBody : public Component
{
public:
	RigidBody();
	virtual ~RigidBody();



public:
	void Start() override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void FixedUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	void OnTrigger();
	void OnCollision();

	void SetBeforePosition();
public:
	// TEST :
	SimpleMath::Vector3 GetBeforePosition();

private:
	// �浹 ó���� ���� ���� �������� ������ �ִ´�.
	SimpleMath::Vector3 m_beforePosition;
	SimpleMath::Vector3 m_beforeRotation;

};

