#pragma once
#include "Component.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"

#include <unordered_map>

using namespace DirectX;

class Transform;

enum class CollisionState
{
	None,
	Enter,
	Stay,
	Exit
};

// static일 경우 다른 충돌체와 체크하지 않는다 일단은
enum class CollisionType
{
	Static,
	Dynamic,
};

// 콜라이더가 부딪히는 것 한정하기 위해.
enum class CollisionWith
{
	All,
	OnlyRay,
	Nothing,
};

class Collision : public Component
{
public:
	Collision();
	virtual ~Collision();

public:
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void SetCenter(const SimpleMath::Vector3& center) abstract;

	void SetIntersect(bool isIntersect);
	bool GetIsIngersect();

	void SetTrigger(bool trigger);
	bool GetIsTrigger();

	CollisionState GetCollisionState();
	void SetCollisionState(const CollisionState& state);

	// 부딪힌 충돌체와 그의 해당하는 스테이트를 넣어준다. 이미 있으면 함수내부에서 걸러준다.
	void AddCollisionDetected(Collision* collision, const CollisionState& state);
	const CollisionState& GetCollisionDetectedByCollisonPointerKey(Collision* collision);
	void SetCollisionDetectedState(Collision* collision, const CollisionState& state);
	
	const CollisionType& GetCollisionType();
	void SetCollisionType(CollisionType type);

	void SetDebugCollisionColor(float r, float g, float b, float a);

	void SetCollisionWith(const CollisionWith& with);
	const CollisionWith& GetCollisionWith();

protected:
	bool m_isIntersect;
	bool m_isTrigger;

	ContainmentType m_containmentType;
	CollisionState m_collisionState;
	CollisionType m_collisionType;
	CollisionWith m_collisionWith;

	std::unordered_map<Collision*, CollisionState> m_detectedCollisionState;

	Vector4 m_debugCollisionColor;
};

