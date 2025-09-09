#include "pch.h"
#include "Blind.h"
#include "JaneD.h"
#include "Chaser.h"
#include "Collision.h"
#include "GameObject.h"
#include "RayComponent.h"
#include "Transform.h"
#include "PlayerComponent.h"
#include "DemonAltarComponent.h"
#include "AStarPathFindComponent.h"
#include "MeshRenderer.h"
#include "RandomNumber.h"

#include "SoundManager.h"
#include "GameManager.h"


Blind::Blind()
{

}

Blind::~Blind()
{

}

void Blind::Awake()
{

}

void Blind::Start()
{
	Super::Start();

	m_model = GetEnemyModel();

	m_model->GetComponent<Transform>()->SetLocalScale({ 0.0014f,0.0014f,0.0014f });

	m_hp = 100.f;
	m_damage = 50.f;
	m_attackSpeed = 2.f;
	m_attackCoolTime = 7.f;
	m_walkSpeed = { 1.f,2.f,2.f };
	m_chaseSpeed = { 1.5f,2.f,3.f };
	m_attackRange = { 2.f,4.f,4.f };
	m_detectRange = { 15.f,15.f,30.f };
	m_sightRange = { 0.f,0.f,0.f };

	m_enemyState = EnemyState::NONE;

	m_altar = GameManager::GetInstance()->GetAltarObject();

	/// 추격 사운드를 위해서
	SoundManager::GetInstance()->PushEnemy(GetOwner());
}

void Blind::FixedUpdate(float dTime)
{

}

void Blind::Update(float dTime)
{
	if (dTime > 0.01)
		return;
	// 여기서 바뀐 상태에 따른 효과를
	m_attackPassingTime += dTime;

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
		/// chase, attack 상태에서 벗어난 상태임
		if (!m_isWalk)
		{
			// 처음 이 상태에 들어오면 walk재생하고 bool값 변경
			SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBlindChannel());
			SoundManager::GetInstance()->PlayBlind(eSOUNDKIND::lBlindWalk);
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
		//TransPlayerPosToTilePos();
		//TransPosToTilePos();
		//std::cout << testTime << std::endl;

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

				/*
				// 시작점
				SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
				// 플레이어 방향으로 레이 발사
				SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
				SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;;
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
						SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fSpotted);
						if (!SoundManager::GetInstance()->GetChase())
						{
							SoundManager::GetInstance()->PlayBGMC(eSOUNDKIND::bChased);
							SoundManager::GetInstance()->DoChase();
						}
						m_nextState = EnemyState::Chase;
					}

				}
				*/

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
			SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBlindChannel());
			SoundManager::GetInstance()->PlayBlind(eSOUNDKIND::lBlindRun);
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
					SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;;
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
				SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;;
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
						if (	 m_isChasing &&
							(SoundManager::GetInstance()->GetEnemyComps()[1]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Walk) ||
							(SoundManager::GetInstance()->GetEnemyComps()[1]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Dead))
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

				// 시작점
				SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
				// 플레이어 방향으로 레이 발사
				SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
				// TODO : 공격을 숨어서 쏘게하는 하드코딩
				SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;;
				SimpleMath::Vector3 direction = playerPos - origin;
				origin += direction * 0.15;
				// 최대거리니까
				float maxDistance = m_attackRange[m_awakenedLevel];

				Collision* hit = nullptr;

				/// Attack 사운드
				/// 재생 중이던 채널의 사운드를 일단 중지
				if (!m_isAttack)
				{
					SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBlindChannel());
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
						// 공격 사운드
						SoundManager::GetInstance()->PlayBlind(eSOUNDKIND::fBlindAttack);
						//std::cout << "Attack" << std::endl;

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
		SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBlindChannel());
		if (!m_isKnifeSound)
		{
			SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBlindChannel());
			SoundManager::GetInstance()->PlayBlind(eSOUNDKIND::fEnemyHit);
			m_isKnifeSound = true;
		}


		m_moveSpeed = 0.f;
		float _storeDamage = m_damage;
		m_damage = 0.f;

		m_isHitByKnife = true;

		if (GameManager::GetInstance()->GetJaneDObject())
		{
			GameManager::GetInstance()->GetJaneDObject()->GetComponent<JaneD>()->SetEnemyKnifeHit(false);
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
			
			if (	 m_isChasing &&
				(SoundManager::GetInstance()->GetEnemyComps()[1]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Walk) ||
				(SoundManager::GetInstance()->GetEnemyComps()[1]->GetComponent<EnemyComponent>()->GetEnemyState() == EnemyState::Dead))
			{
				SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fEscaped);
				SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBGMCChannel());
				SoundManager::GetInstance()->DoEscape();
				m_isChasing = false;
			}
			m_nextState = EnemyState::Walk;
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

		m_pOwner->GetComponent<Collision>()->SetCollisionWith(CollisionWith::Nothing);
		m_pOwner->GetComponent<Transform>()->SetPosition({ -100.f,-100.f,-100.f });

		// 사망 사운드
		if (!m_isDead)
		{
			SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBlindChannel());
			SoundManager::GetInstance()->PlayBlind(eSOUNDKIND::fMaleScream);
			SoundManager::GetInstance()->AddReverb(SoundManager::GetInstance()->GetBlindChannel());
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

void Blind::LateUpdate(float dTime)
{
	// 여기는 바뀐 상태마저 넘어서는 무언가를..?


	
	if (m_nextState != EnemyState::Dead && m_hp <= 0.0f)
	{
		//std::cout << "Blind Dead" << std::endl;
		
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
		//std::cout << "Blind Animation State" << std::endl;
		m_model->GetComponent<MeshRenderer>()->SetAnimationState(2);
		m_enemyState = m_nextState;
	}
}

void Blind::Render()
{
	// 시작점
// 	SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
// 	// 플레이어 방향으로 레이 발사
// 	SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
// 	SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;
// 	SimpleMath::Vector3 direction = playerPos - origin;
// 	origin += direction * 0.15;
// 	m_renderer->DrawDebugingRay(
// 		{ origin.x, origin.y, origin.z, 1.f },
// 		{ direction.x, direction.y, direction.z, 1.f },
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

void Blind::Release()
{

}

void Blind::OnCollisionEnter(Collision* collision)
{

}

void Blind::OnCollisionStay(Collision* collision)
{

}

void Blind::OnCollisionExit(Collision* collision)
{

}
