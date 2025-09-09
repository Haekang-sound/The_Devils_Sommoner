#pragma once
#include "Component.h"

class Transform;

/// <summary>
/// 오브젝트의 이동을 담당하는 컴포넌트
/// 다른 컴포넌트안에서 컨트롤러 컴포넌트의 이동함수를 호출한다.
/// 그러면 이동한다! 
/// </summary>
class Move : public Component
{
public:
	Move();

public:
	// IComponent을(를) 통해 상속됨
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

	// 움직여라

public:
	// 이동 
	void TransportPositiveX(float dTime);	// 1. x축 이동 +
	void TransportNegativeX(float dTime);	// 1. x축 이동 -
	void TransportPositiveZ(float dTime);	// 2. z축 이동 +
	void TransportNegativeZ(float dTime);	// 2. z축 이동 -
	void TransportPositiveY(float dTime);	// 3. y축 이동 +
	void TransportNegativeY(float dTime);	// 3. y축 이동 -

	// 회전
	void RotatePositiveX(float radian);	// 1. x축 회전 +
	void RotateNegativeX(float radian);	// 1. x축 회전 -
	void RotatePositiveY(float radian);	// 2. y축 회전 +
	void RotateNegativeY(float radian);	// 2. y축 회전 -
	void RotatePositiveZ(float radian);	// 3. z축 회전 +
	void RotateNegativeZ(float radian);	// 3. z축 회전 -

protected:
	Transform* m_transform;
	SimpleMath::Vector3 m_pos;
	SimpleMath::Vector3 m_rot;
	float speed;


};