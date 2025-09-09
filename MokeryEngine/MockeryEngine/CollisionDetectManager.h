#pragma once
#include "../Libraries/DXTK/Inc/SimpleMath.h"
#include <vector>
#include <functional>

class Collision;
class BoxCollision;
class SphereCollision;

using namespace DirectX;

/// <summary>
/// ���� �浹ü�� �˻��� ����.
/// 2024.02.01 - ���Լ�
/// </summary>
/// 
class ID3DRenderer;

class CollisionDetectManager
{
public:
	CollisionDetectManager();
	~CollisionDetectManager();

public:
	void Init();
	void Update();
	void Finalize();

	void AddBoxCollision(BoxCollision* collision);
	void AddSphereCollision(SphereCollision* collision);
	
	void CheckCollisionDetection();
	void CheckCollisionDetection2();
	void CheckCollisionDetection3();

	Collision* CheckRay(const SimpleMath::Vector3& origin, const SimpleMath::Vector3& direction, float distance);
	Collision* CheckRay(const SimpleMath::Vector3& origin, const SimpleMath::Vector3& direction, float distance, std::function<bool(Collision*)> func);

private:
	std::vector<BoxCollision*> m_boxes;
	std::vector<SphereCollision*> m_spheres;

public:
	void ObjectCulling();
	void SetRenderer(ID3DRenderer* renderer);

private:
	SimpleMath::Matrix m_cameraProj;
	BoundingFrustum m_boundingFrustum;

	ID3DRenderer* m_renderer;
};