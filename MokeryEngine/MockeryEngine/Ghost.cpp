#include "pch.h"
#include "Ghost.h"
#include "Collision.h"
#include "GameObject.h"
#include "Transform.h"
#include "PlayerComponent.h"
#include "AStarPathFindComponent.h"
#include "RandomNumber.h"
#include "MeshRenderer.h"
#include "GameManager.h"

#include "SoundManager.h"

Ghost::Ghost()
	: m_isDisturbing(false)
{

}

Ghost::~Ghost()
{

}

void Ghost::Start()
{
	Super::Start();

	m_model = GetEnemyModel();

	m_hp = 100.f;
	m_damage = 0.f;
	m_attackSpeed = 0.f;
	m_walkSpeed = { 1.5f,1.5f,1.5f };
	m_chaseSpeed = { 0.f,0.f,0.f };
	m_attackRange = { 2.f,20.f,20.f };
	m_detectRange = { 0.f,0.f,0.f };
	m_sightRange = { 0.f,0.f,0.f };

	m_enemyState = EnemyState::NONE;

	SoundManager::GetInstance()->PlayGhost(eSOUNDKIND::lGhostWalk);
}

void Ghost::FixedUpdate(float dTime)
{

}

void Ghost::Update(float dTime)
{
	m_moveSpeed = m_walkSpeed[m_awakenedLevel];

	m_passingTime += dTime;

	switch (m_enemyState)
	{
	case EnemyState::NONE:
	{

	}
	break;

	case EnemyState::Walk:
	{
		// 애니메이션
		m_model->GetComponent<MeshRenderer>()->SetAnimationState(2);


		if (CheckNextTile())
		{
			// TEST : 시간이 넘으면 내 위치로 다시 길을 찾을 수 있게 하는 목적
			//if(InputManager::GetInstance()->m_Keyboard.IsKeyHold('V'))
			if (m_passingTime > 5.f)
			{
				//std::cout << "Re Find" << std::endl;
				m_passingTime = 0.f;
				//float tileSize = m_astar->GetTileSize();
				PathPos startPos = TransPosToTilePos();
				//m_transform->SetPosition({ startPos.y * tileSize ,0.f, startPos.x * tileSize });
				int x = m_pOwner->GetComponent<RandomNumber>()->GetRandomInt(0, m_astar->GetMapSize() - 1);
				int z = m_pOwner->GetComponent<RandomNumber>()->GetRandomInt(0, m_astar->GetMapSize() - 1);
				PathPos destPos = { x,z };

				if (m_astar->IsWallExist(destPos))
				{
					//std::cout << "Can't go there!" << std::endl;
					break;
				}

				//std::cout << "StartPos : " << startPos.y << ", " << startPos.x << std::endl;
				//std::cout << "DestPos: " << destPos.y << ", " << destPos.x << std::endl;

				m_astar->SetStartPos(startPos);
				m_astar->SetDestination(destPos);
				FindPath();
				break;
			}
			else
			{
				FindNextTile();
			}
		}
		else
		{
			SimpleMath::Vector3	currentPos = m_transform->GetPosition();
			currentPos += (m_moveSpeed * dTime) * m_dirToNextPos;
			m_transform->SetPosition(currentPos);
		}
	}
	break;
	}


	if (PlayerTracker(m_attackRange[m_awakenedLevel], m_pOwner->GetComponent<Transform>()->GetPosition(), m_player->GetComponent<Transform>()->GetPosition()))
	{
		m_isDisturbing = true;
	}
	else
	{
		m_isDisturbing = false;
	}


	// 회전각
	float rot = 0.f;

	// 왼쪽
	if (m_dirToNextPos.x == 1.f)
	{
		rot = -90.f * 3.141592f / 180.f;
	}

	// 오른쪽
	else if (m_dirToNextPos.x == -1.f)
	{
		rot = 90.f * 3.141592f / 180.f;
	}

	// 앞
	else if (m_dirToNextPos.z == 1.f)
	{
		rot = 180.f * 3.141592f / 180.f;
	}

	// 뒤
	else if (m_dirToNextPos.z == -1.f)
	{
		rot = 0.f * 3.141592f / 180.f;
	}

	
	m_pOwner->GetComponent<Transform>()->SetRotation({ 0.f,rot,0.f });

}

void Ghost::LateUpdate(float dTime)
{
	if (!m_isStart && GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->GetGameStart())
	{
		m_enemyState = EnemyState::Walk;
		m_isStart = true;
	}
}

void Ghost::Render()
{

}

void Ghost::Release()
{

}

void Ghost::OnCollisionEnter(Collision* collision)
{

}

void Ghost::OnCollisionStay(Collision* collision)
{

}

void Ghost::OnCollisionExit(Collision* collision)
{

}
