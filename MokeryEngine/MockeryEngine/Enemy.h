#pragma once
#include "Component.h"
#include "CommonStructs.h"
#include "../Libraries/DXTK/Inc/SimpleMath.h"

using namespace DirectX;
class AStarPathFindComponent;
class Transform;

class Enemy : public Component
{
public:
	Enemy();
	virtual ~Enemy();

public:
	void Start() override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void FixedUpdate(float dTime) override;
	void Render() override;
	void Release() override;

	void SetRandomDestination();

	void SetSpeed(const float& speed);

private:
	bool CheckNextTile();
	void FindNextTile();
	void Walk();

	void PathFind();

	// 시작 위치를 정한다.
	void SetStartPos(PathPos pos);

private:
	AStarPathFindComponent* m_astar;
	Transform* m_transform;

	//EnemyState m_enemyState;

	PathPos m_startPathPos;
	PathPos m_nextPathPos;

	SimpleMath::Vector3 m_nextPos;
	SimpleMath::Vector3 m_dirToNextPos;

	// 이동할때 스피드
	float m_speed;
};