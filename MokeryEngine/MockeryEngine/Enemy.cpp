#include "pch.h"
#include "Enemy.h"
#include "AStarPathFindComponent.h"
#include "GameObject.h"
#include "Transform.h"

Enemy::Enemy()
	:
	m_transform(nullptr),
	//m_enemyState(EnemyState::Idle),
	m_startPathPos({ 0,0 }),
	m_nextPathPos({ 0,0 }),
	m_nextPos(),
	m_speed(0.f)
{

}

Enemy::~Enemy()
{

}

void Enemy::Start()
{
	m_astar = m_pOwner->GetComponent<AStarPathFindComponent>();
	m_transform = m_pOwner->GetComponent<Transform>();
	m_astar->SetStartPos(m_startPathPos);
	PathFind();
	SetRandomDestination();
}

void Enemy::Update(float dTime)
{
	//SimpleMath::Vector3	pos = m_transform->GetPosition();
	////std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
	//std::cout << dTime << std::endl;

	if (CheckNextTile())
	{
		FindNextTile();
	}
	else
	{
		SimpleMath::Vector3	currentPos = m_transform->GetPosition();
		currentPos += (m_speed * dTime) * m_dirToNextPos;
		m_transform->SetPosition(currentPos);
	}
}

void Enemy::FixedUpdate(float dTime)
{
}

void Enemy::LateUpdate(float dTime)
{
}

void Enemy::Render()
{
}

void Enemy::Release()
{
}

void Enemy::SetRandomDestination()
{
	//// TODO : ·£´ýÀ¸·Î ¹Ù²ãÁà¾ß ÇÔ.
	//m_astar->SetDestination({13,13});
	//m_astar->AstarPathFinding();
}

bool Enemy::CheckNextTile()
{
	SimpleMath::Vector3 currentPos = m_transform->GetPosition();

	float offset = 0.1f;
	if (fabs(m_nextPos.x - currentPos.x) < offset
		&& fabs(m_nextPos.y - currentPos.y) < offset
		&& fabs(m_nextPos.z - currentPos.z) < offset)
	{
		return true;
	}

	return false;
}

void Enemy::FindNextTile()
{
	TileInfo nextTileInfo = m_astar->GetNextPos(m_transform->GetPosition());
	m_nextPos = nextTileInfo.tilePos;
	m_dirToNextPos = m_nextPos - m_transform->GetPosition();
	m_dirToNextPos.Normalize();
}

void Enemy::Walk()
{

}

void Enemy::PathFind()
{
	m_astar->AstarPathFinding();
}

void Enemy::SetStartPos(PathPos pos)
{
	m_startPathPos = pos;
}

void Enemy::SetSpeed(const float& speed)
{
	m_speed = speed;
}

