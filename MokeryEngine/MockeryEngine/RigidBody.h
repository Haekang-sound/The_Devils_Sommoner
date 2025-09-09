#pragma once
#include "Component.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"

using namespace DirectX;

/// <summary>
/// 충돌 처리를 위한 컴포넌트
/// 사실 애매한 포지션이다 
/// 2024.02.01 - 강규석
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
	// 충돌 처리를 위해 이전 포지션을 가지고 있는다.
	SimpleMath::Vector3 m_beforePosition;
	SimpleMath::Vector3 m_beforeRotation;

};

