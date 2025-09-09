#pragma once
#include "Component.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"

using namespace DirectX;

class Transform;

// 일단 이름이 겹쳐서 수정
enum class KnifeObjectState
{
	Idle,
	Shoot,
};

class KnifeComponent : public Component
{
public:
	KnifeComponent();
	virtual ~KnifeComponent();


	void OnCollisionEnter(Collision* collision) override;

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	void Shoot(const SimpleMath::Vector3& position, const SimpleMath::Vector3& direction, const SimpleMath::Vector3& rotation);
	void SetDirection(const SimpleMath::Vector3& direction);
	void SetSpeed(const float& speed);

	void SetState(const KnifeObjectState& state);
private:
	Transform* m_transform;

private:
	KnifeObjectState m_state;
	SimpleMath::Vector3 m_dir;
	float m_speed;
};