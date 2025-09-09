#pragma once
#include "Collision.h"

class SphereCollision : public Collision
{
	using Super = Collision;
public:
	SphereCollision();
	virtual ~SphereCollision();

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

	const BoundingSphere& GetBoundingSphere();

public:
	virtual void SetCenter(const SimpleMath::Vector3& center) override;
	void SetRadius(const float& radius);

private:
	BoundingSphere m_boundingSphere;

	Transform* m_transform;
};

