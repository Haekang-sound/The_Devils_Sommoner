#include "pch.h"
#include "JaneD.h"
#include "Blind.h"
#include "Chaser.h"
#include "Collision.h"
#include "GameObject.h"
#include "RayComponent.h"
#include "Transform.h"
#include "PlayerComponent.h"
#include "DemonAltarComponent.h"
#include "AStarPathFindComponent.h"
#include "RandomNumber.h"
#include "MeshRenderer.h"

#include "SoundManager.h"
#include "GameManager.h"

JaneD::JaneD()
{

}

JaneD::~JaneD()
{

}

void JaneD::Awake()
{

}

void JaneD::Start()
{
	Super::Start();

	m_model = GetEnemyModel();

	m_hp = 100.f;
	m_damage = 40.f;
	m_attackSpeed = 2.f;
	m_attackCoolTime = 7.f;
	m_walkSpeed = { 1.5f,2.f,2.f };
	m_chaseSpeed = { 2.5f,2.5f,3.f };
	m_attackRange = { 2.f,4.f,4.f };
	m_detectRange = { 5.f,5.f,10.f };
	m_sightRange = { 10.f,10.f,20.f };

	m_enemyState = EnemyState::NONE;

	m_altar = GameManager::GetInstance()->GetAltarObject();

	/// 추격 사운드를 위해서
	SoundManager::GetInstance()->PushEnemy(GetOwner());
}

void JaneD::FixedUpdate(float dTime)
{

}

void JaneD::Update(float dTime)
{
	if (dTime > 0.01)
		return;
	// 여기서 상태가 바뀌는 경우를 
	m_attackPassingTime += dTime;

	// 여기서 바뀐 상태에 따른 효과를
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

		/// Walk 상태에 들어왔다면
		if (!m_isWalk)
		{
			// 처음 이 상태에 들어오면 walk재생하고 bool값 변경
			SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetJaneChannel());
			SoundManager::GetInstance()->PlayJane(eSOUNDKIND::lJaneWalk);
			m_isWalk = true;
			m_isChase = false;
			m_isAttack = false;
		}


		if (m_onFindDoor)
		{
			bool findDoor = InteractWithDoor(dTime);
			if (findDoor)
			{
				m_enemyState = EnemyState::Interact;
			}
		}

		m_moveSpeed = m_walkSpeed[m_awakenedLevel];

		m_passingTime += dTime;

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
				m_beforeState = m_enemyState;
				FindNextTile();
			}

			if (PlayerTracker(m_detectRange[m_awakenedLevel], m_pOwner->GetComponent<Transform>()->GetPosition(), m_player->GetComponent<Transform>()->GetPosition()))
			{
				// 시작점
				SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
				// 플레이어 방향으로 레이 발사
				SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
				SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;
				SimpleMath::Vector3 direction = playerPos - origin;
				origin += direction * 0.15;
				// 최대거리니까
				float maxDistance = m_detectRange[m_awakenedLevel];


				Collision* hit = nullptr;


				m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit);
				if (hit)
				{
					if (hit->GetOwner()->GetName() == "Player")
					{
						//std::cout << "Walk To Chase" << std::endl;
						if (!m_isChasing)
						{
							SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fSpotted);
							m_isChasing = true;
						}
						if (!SoundManager::GetInstance()->GetChase())
						{
							SoundManager::GetInstance()->PlayBGMC(eSOUNDKIND::bChased);
							SoundManager::GetInstance()->DoChase();
						}
						m_nextState = EnemyState::Chase;
					}

				}

			}

			else if (PlayerTracker(m_sightRange[m_awakenedLevel], m_pOwner->GetComponent<Transform>()->GetPosition(), m_player->GetComponent<Transform>()->GetPosition()))
			{
				/// 정면
				// 시작점
				SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
				SimpleMath::Vector3 direction = m_dirToNextPos;

				origin += direction * 0.4f;
				//direction *= m_sightRange[m_awakenedLevel];
				// 최대거리니까
				float maxDistance = m_sightRange[m_awakenedLevel];

				Collision* hit = nullptr;

				m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit);

				/// 정면왼쪽
				// 시작점
				SimpleMath::Vector3 origin2 = m_pOwner->GetComponent<Transform>()->GetPosition();
				SimpleMath::Vector3 direction2 = m_dirToNextPos;

				origin2 += direction2 * 0.4f;
				//direction2 *= m_sightRange[m_awakenedLevel];
				if (direction2.x != 0.f)
				{
					direction2.z -= 2.f;
				}
				else if (direction2.z != 0.f)
				{
					direction2.x -= 2.f;
				}

				Collision* hit2 = nullptr;

				m_pOwner->GetComponent<RayComponent>()->Ray(origin2, direction2, maxDistance, &hit2);

				/// 정면오른쪽
				// 시작점
				SimpleMath::Vector3 origin3 = m_pOwner->GetComponent<Transform>()->GetPosition();
				SimpleMath::Vector3 direction3 = m_dirToNextPos;

				origin3 += direction3 * 0.4f;
				//direction3 *= m_sightRange[m_awakenedLevel];
				if (direction3.x != 0.f)
				{
					direction3.z += 2.f;
				}
				else if (direction3.z != 0.f)
				{
					direction3.x += 2.f;
				}

				Collision* hit3 = nullptr;

				m_pOwner->GetComponent<RayComponent>()->Ray(origin3, direction3, maxDistance, &hit3);


				if (hit)
				{
					if (hit->GetOwner()->GetName() == "Player")
					{
						//std::cout << "Walk To Chase" << std::endl;
						m_nextState = EnemyState::Chase;
					}

				}

				if (hit2)
				{
					if (hit2->GetOwner()->GetName() == "Player")
					{
						//std::cout << "Walk To Chase" << std::endl;
						m_nextState = EnemyState::Chase;
					}

				}

				if (hit3)
				{
					if (hit3->GetOwner()->GetName() == "Player")
					{
						//std::cout << "Walk To Chase" << std::endl;
						m_nextState = EnemyState::Chase;
					}

				}

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

	case EnemyState::Interact:
	{
		// 1. 레이를 쏜다.
		// 2. 레이에 검출된 것이 없으면 그냥 지나간다.
		// 3. 레이에 문이 검출되면 일단 문의 스테이트를 검사한다.
		// 4. 문이 닫혀있을 경우 문을 연다. -> 상호작용 시간 필요
		// 2, 4번에서 문을 열었으면 다시 이동하기위해 Chase로 바꾼다.
		// 

		// 애니메이션
		m_model->GetComponent<MeshRenderer>()->PlayAnimationOnce(0);


		bool isDoorExist = InteractWithDoor(dTime);

		if (!isDoorExist)
		{
			//std::cout << "Interact To Chase" << std::endl;
			m_enemyState = m_beforeState;
			m_beforeState = EnemyState::NONE;
			m_onFindDoor = false;
		}
	}
	break;

	case EnemyState::Chase:
	{
		// 애니메이션
		m_model->GetComponent<MeshRenderer>()->SetAnimationState(2);

		/// Chase상태라면
		if (!m_isChase)
		{
			SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetJaneChannel());
			SoundManager::GetInstance()->PlayJane(eSOUNDKIND::lJaneRun);
			m_isWalk = false;
			m_isChase = true;
			m_isAttack = false;
		}

		if (m_onFindDoor)
		{
			bool findDoor = InteractWithDoor(dTime);
			if (findDoor)
			{
				m_enemyState = EnemyState::Interact;
			}
		}

		m_moveSpeed = m_chaseSpeed[m_awakenedLevel];


		m_passingTime += dTime;

		if (CheckNextTile())
		{
			// TEST : 시간이 넘으면 내 위치로 다시 길을 찾을 수 있게 하는 목적
			if (m_passingTime > 1.f)
			{
				//std::cout << "Re Find" << std::endl;
				m_passingTime = 0.f;
				//float tileSize = m_astar->GetTileSize();
				PathPos startPos = TransPosToTilePos();
				//m_transform->SetPosition({ startPos.y * tileSize ,0.f, startPos.x * tileSize });
				PathPos destPos = TransPlayerPosToTilePos();

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
				m_beforeState = m_enemyState;
				FindNextTile();
			}

			if (PlayerTracker(m_attackRange[m_awakenedLevel], m_pOwner->GetComponent<Transform>()->GetPosition(), m_player->GetComponent<Transform>()->GetPosition()))
			{
				if (m_attackPassingTime >= m_attackCoolTime)
				{
					// 시작점
					SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
					// 플레이어 방향으로 레이 발사
					SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
					SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;
					SimpleMath::Vector3 direction = playerPos - origin;
					origin += direction * 0.15;
					// 최대거리니까
					float maxDistance = m_attackRange[m_awakenedLevel];


					Collision* hit = nullptr;


					m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit);
					if (hit)
					{
						if (hit->GetOwner()->GetName() == "Player")
						{
							//std::cout << "Chase To Attack" << std::endl;
							m_nextState = EnemyState::Attack;
						}
					}
				}
			}

			else if (!PlayerTracker(m_detectRange[m_awakenedLevel], m_pOwner->GetComponent<Transform>()->GetPosition(), m_player->GetComponent<Transform>()->GetPosition()))
			{
				// 시작점
				SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
				// 플레이어 방향으로 레이 발사
				SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
				SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;
				SimpleMath::Vector3 direction = playerPos - origin;
				origin += direction * 0.15;
				// 최대거리니까
				float maxDistance = m_detectRange[m_awakenedLevel];


				Collision* hit = nullptr;


				m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit);
				if (hit)
				{
					if (hit->GetOwner()->GetName() != "Player")
					{
						//std::cout << "Chase To Walk" << std::endl;
						if ( m_isChasing &&
							(SoundManager::GetInstance()->GetEnemyComps()[0]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Walk) ||
							(SoundManager::GetInstance()->GetEnemyComps()[0]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Dead))
						{
							SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fEscaped);
							SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBGMCChannel());
							SoundManager::GetInstance()->DoEscape();
							m_isChasing = false;
						}
						m_nextState = EnemyState::Walk;
					}
				}
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

	case EnemyState::Attack:
	{
		// 공격애니메이션이 끝났는지도 봐야됨
		if (m_attackPassingTime >= m_attackCoolTime)
		{
			// TODO : 공격중에 움직이나?
			m_moveSpeed = 0.f;

			m_passingTime += dTime;

			if (m_passingTime >= m_attackSpeed)
			{
				// 애니메이션
				m_model->GetComponent<MeshRenderer>()->PlayAnimationOnce(0);

				SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
				// 플레이어 방향으로 레이 발사
				SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
				// TODO : 공격을 숨어서 쏘게하는 하드코딩 (얘가 제일 심함...)
				SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;
				SimpleMath::Vector3 direction = playerPos - origin;
				origin += direction * 0.15;
				// 최대거리니까
				float maxDistance = m_attackRange[m_awakenedLevel];


				Collision* hit = nullptr;


				/// Attack 사운드
				/// 재생 중이던 채널의 사운드를 일단 중지
				if (!m_isAttack)
				{
					SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetJaneChannel());
					m_isAttack = true;
					m_isChase = false;
					m_isWalk = false;
				}

				m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit);

				// 때리려는데 플레이어가 없으면 다시 쫓아가기
				if (hit)
				{
					if (hit->GetOwner()->GetName() == "Player")
					{
						//std::cout << "Attack" << std::endl;
						SoundManager::GetInstance()->PlayJane(eSOUNDKIND::fJaneAttack);

						hit->GetOwner()->GetComponent<PlayerComponent>()
							->SetHp(m_player->GetComponent<PlayerComponent>()->GetHp() - m_damage);
						SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fPhit);
						// 시작점
						SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
						// 플레이어 방향으로 레이 발사
						SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
						SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;
						SimpleMath::Vector3 direction = playerPos - origin;
						origin += direction * 0.15;
						// 최대거리니까
						float maxDistance = m_attackRange[m_awakenedLevel];


						Collision* hit2 = nullptr;
						m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit2);
						if (hit2)
						{
							if (hit2->GetOwner()->GetName() == "Player")
							{
								m_nextState = EnemyState::Attack;

							}
						}
					}
					else
					{
						//std::cout << "Attack To Chase" << std::endl;
						
						m_nextState = EnemyState::Chase;
					}
				}
				else
				{
					//std::cout << "Attack To Chase" << std::endl;
					
					m_nextState = EnemyState::Chase;
				}
				m_passingTime = 0.f;
				m_attackPassingTime = 0.f;
			}
		}
		else
		{
			// 시작점
			SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
			// 플레이어 방향으로 레이 발사
			SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
			SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;
			SimpleMath::Vector3 direction = playerPos - origin;
			origin += direction * 0.15;
			// 최대거리니까
			float maxDistance = m_attackRange[m_awakenedLevel];


			Collision* hit3 = nullptr;
			m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit3);
			if (hit3)
			{
				if (hit3->GetOwner()->GetName() != "Player")
				{
					m_nextState = EnemyState::Chase;
				}
			}
			else
			{
				m_nextState = EnemyState::Chase;
			}
		}
	}
	break;

	case EnemyState::Stun:
	{
		// 애니메이션
		m_model->GetComponent<MeshRenderer>()->SetAnimationState(1);

		/// 스턴 하면 일시 중지
		SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetJaneChannel());

		m_moveSpeed = 0.f;
		float _storeDamage = m_damage;
		m_damage = 0.f;

		m_isHitByKnife = true;

		if (GameManager::GetInstance()->GetBlindObject())
		{
			GameManager::GetInstance()->GetBlindObject()->GetComponent<Blind>()->SetEnemyKnifeHit(false);
		}
		if (GameManager::GetInstance()->GetChaserObject())
		{
			GameManager::GetInstance()->GetChaserObject()->GetComponent<Chaser>()->SetEnemyKnifeHit(false);
		}

		m_stunPassingTime += dTime;
		if (m_stunPassingTime >= 10.f)
		{
			m_stunPassingTime = 0.f;
			m_damage = _storeDamage;

			//std::cout << "Stun To Walk" << std::endl;
			m_nextState = EnemyState::Walk;
			if ( m_isChasing &&
				(SoundManager::GetInstance()->GetEnemyComps()[0]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Walk) ||
				(SoundManager::GetInstance()->GetEnemyComps()[0]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Dead))
			{
				SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fEscaped);
				SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBGMCChannel());
				SoundManager::GetInstance()->DoEscape();
				m_isChasing = false;
			}

			m_isKnifeSound = false;
		}


	}
	break;

	case EnemyState::Dead:
	{
		m_walkSpeed[m_awakenedLevel] = 0.0f;
		m_chaseSpeed[m_awakenedLevel] = 0.0f;
		m_damage = 0.0f;
		m_isHitByKnife = false;

		m_pOwner->SetIsDrawRecursively(false);
		m_pOwner->SetIsActive(false);
		
		m_pOwner->GetComponent<Collision>()->SetCollisionWith(CollisionWith::Nothing);
		m_pOwner->GetComponent<Transform>()->SetPosition({ -100.f,-100.f,-100.f });

		// 사망 사운드
		if (!m_isDead)
		{
			SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetJaneChannel());
			SoundManager::GetInstance()->PlayJane(eSOUNDKIND::fFemaleScream);
			SoundManager::GetInstance()->AddReverb(SoundManager::GetInstance()->GetJaneChannel());
			SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBGMCChannel());

			m_isDead = true;
		}
	}
	break;
	}



	for (auto e : m_altar)
	{
		if (m_isHitByKnife
			&& e->GetComponent<DemonAltarComponent>()->GetisAltarActivated())
		{
			m_hp = 0.f;
		}
	}

	// 회전각
	float rot = 0.f;

	// 왼쪽
	if (m_dirToNextPos.x >= 1.f)
	{
		rot = -90.f * 3.141592f / 180.f;
	}

	// 오른쪽
	else if (m_dirToNextPos.x <= -1.f)
	{
		rot = 90.f * 3.141592f / 180.f;
	}

	// 앞
	else if (m_dirToNextPos.z >= 1.f)
	{
		rot = 180.f * 3.141592f / 180.f;
	}

	// 뒤
	else if (m_dirToNextPos.z <= -1.f)
	{
		rot = 0.f * 3.141592f / 180.f;
	}

	if (m_enemyState == EnemyState::Attack)
	{
		// 이 녀석은 태생부터 달라먹어서 만든 방법
		SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
		SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
		rot = -atan2((playerPos.z - enemyPos.z), (playerPos.x - enemyPos.x)) - 90.f * 3.141592f / 180.f;
	}
	m_pOwner->GetComponent<Transform>()->SetRotation({ 0.f,rot,0.f });
}

void JaneD::LateUpdate(float dTime)
{
	// 여기는 바뀐 상태마저 넘어서는 무언가를..?
	
	if (m_nextState != EnemyState::Dead && m_hp <= 0.0f)
	{
		//std::cout << "JaneD Dead" << std::endl;
	
		m_nextState = EnemyState::Dead;
		if (m_awakenedLevel < 2)
		{
			m_awakenedLevel++;
		}
	}

	if (!m_isStart && GameManager::GetInstance()->GetPlayerObject()->GetComponent<PlayerComponent>()->GetGameStart())
	{
		
		m_nextState = EnemyState::Walk;
		m_isStart = true;
	}

	if (m_model->GetComponent<MeshRenderer>()->IsFinishAnimation())
	{
		m_model->GetComponent<MeshRenderer>()->SetAnimationState(2);
		m_enemyState = m_nextState;
	}
}

void JaneD::Render()
{
// 	SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
// 	SimpleMath::Vector3 direction = m_dirToNextPos;
// 
// 	origin += direction * 0.4f;
// 	direction *= m_sightRange[m_awakenedLevel];
// 	m_renderer->DrawDebugingRay(
// 		{ origin.x, origin.y, origin.z, 1.f },
// 		{ direction.x, direction.y, direction.z, 1.f },
// 		{ 1.f,0.f,0.f,1.f },
// 		false
// 	);
// 	SimpleMath::Vector3 origin2 = m_pOwner->GetComponent<Transform>()->GetPosition();
// 	SimpleMath::Vector3 direction2 = m_dirToNextPos;
// 
// 	origin2 += direction2 * 0.4f;
// 	direction2 *= m_sightRange[m_awakenedLevel];
// 	if (direction2.x != 0.f)
// 	{
// 		direction2.z -= 2.f;
// 	}
// 	else if (direction2.z != 0.f)
// 	{
// 		direction2.x -= 2.f;
// 	}
// 	m_renderer->DrawDebugingRay(
// 		{ origin2.x, origin2.y, origin2.z, 1.f },
// 		{ direction2.x, direction2.y, direction2.z, 1.f },
// 		{ 0.f,1.f,0.f,1.f },
// 		false
// 	);
// 	SimpleMath::Vector3 origin3 = m_pOwner->GetComponent<Transform>()->GetPosition();
// 	SimpleMath::Vector3 direction3 = m_dirToNextPos;
// 
// 	origin3 += direction3 * 0.4f;
// 	direction3 *= m_sightRange[m_awakenedLevel];
// 	if (direction3.x != 0.f)
// 	{
// 		direction3.z += 2.f;
// 	}
// 	else if (direction3.z != 0.f)
// 	{
// 		direction3.x += 2.f;
// 	}
// 	m_renderer->DrawDebugingRay(
// 		{ origin3.x, origin3.y, origin3.z, 1.f },
// 		{ direction3.x, direction3.y, direction3.z, 1.f },
// 		{ 0.f,0.f,1.f,1.f },
// 		false
// 	);
// 	// 시작점
// 	SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
// 	// 플레이어 방향으로 레이 발사
// 	SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
// 	SimpleMath::Vector3 origin4 = enemyPos + (playerPos - enemyPos) * 0.1f;
// 	SimpleMath::Vector3 direction4 = playerPos - origin4;
// 	origin4 += direction4 * 0.15;
// 	m_renderer->DrawDebugingRay(
// 		{ origin4.x, origin4.y, origin4.z, 1.f },
// 		{ direction4.x, direction4.y, direction4.z, 1.f },
// 		{ 1.f,0.f,0.f,1.f },
// 		false
// 	);


	if (m_isHitByKnife)
	{
		m_knifeCheckBox.Center = m_pOwner->GetComponent<Transform>()->GetPosition();
		m_knifeCheckBox.Extents = { 0.08f,0.08f,0.08f };

		m_renderer->DrawDebugingBoundingBox({ m_knifeCheckBox.Center.x, m_knifeCheckBox.Center.y + 1.2f, m_knifeCheckBox.Center.z },
			{ m_knifeCheckBox.Extents.x, m_knifeCheckBox.Extents.y, m_knifeCheckBox.Extents.z },
			{ 0.f,0.f,0.f,0.f }, { 1.f,1.f,1.f,1.f }
		);
	}
}

void JaneD::Release()
{

}

void JaneD::OnCollisionEnter(Collision* collision)
{

}

void JaneD::OnCollisionStay(Collision* collision)
{

}

void JaneD::OnCollisionExit(Collision* collision)
{

}
