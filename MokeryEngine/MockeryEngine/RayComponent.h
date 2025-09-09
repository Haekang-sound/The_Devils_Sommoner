#pragma once
#include "Component.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"

#include <functional>

class Collision;
class CollisionDetectManager;

class RayComponent : public Component
{
public:
	RayComponent();
	virtual ~RayComponent();

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	void SetCollisionDetectManager(CollisionDetectManager* manager);
	void Ray(const SimpleMath::Vector3& origin, SimpleMath::Vector3 direction, float distance, Collision** outCollision);
	void Ray(const SimpleMath::Vector3& origin, SimpleMath::Vector3 direction, float distance, Collision** outCollision, std::function<bool(Collision*)> func);

private:
	CollisionDetectManager* m_collisionDetectManager;
};

