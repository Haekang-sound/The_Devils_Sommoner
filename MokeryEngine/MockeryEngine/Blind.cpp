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

	/// �߰� ���带 ���ؼ�
	SoundManager::GetInstance()->PushEnemy(GetOwner());
}

void Blind::FixedUpdate(float dTime)
{

}

void Blind::Update(float dTime)
{
	if (dTime > 0.01)
		return;
	// ���⼭ �ٲ� ���¿� ���� ȿ����
	m_attackPassingTime += dTime;

	switch (m_enemyState)
	{
	case EnemyState::NONE:
	{

	}
	break;

	case EnemyState::Walk:
	{
		// �ִϸ��̼�
		m_model->GetComponent<MeshRenderer>()->SetAnimationState(2);

		/// Walk ���¿� ���Դٸ�
		/// chase, attack ���¿��� ��� ������
		if (!m_isWalk)
		{
			// ó�� �� ���¿� ������ walk����ϰ� bool�� ����
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
			// TEST : �ð��� ������ �� ��ġ�� �ٽ� ���� ã�� �� �ְ� �ϴ� ����
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
				// ������
				SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
				// �÷��̾� �������� ���� �߻�
				SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
				SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;;
				SimpleMath::Vector3 direction = playerPos - origin;
				origin += direction * 0.15;

				// �ִ�Ÿ��ϱ�
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
		// 1. ���̸� ���.
		// 2. ���̿� ����� ���� ������ �׳� ��������.
		// 3. ���̿� ���� ����Ǹ� �ϴ� ���� ������Ʈ�� �˻��Ѵ�.
		// 4. ���� �������� ��� ���� ����. -> ��ȣ�ۿ� �ð� �ʿ�
		// 2, 4������ ���� �������� �ٽ� �̵��ϱ����� Chase�� �ٲ۴�.
		// 

		// �ִϸ��̼�
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
		// �ִϸ��̼�
		m_model->GetComponent<MeshRenderer>()->SetAnimationState(2);

		/// Chase���¶��
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
			// TEST : �ð��� ������ �� ��ġ�� �ٽ� ���� ã�� �� �ְ� �ϴ� ����
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
					// ������
					SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
					// �÷��̾� �������� ���� �߻�
					SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
					SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;;
					SimpleMath::Vector3 direction = playerPos - origin;
					origin += direction * 0.15;

					// �ִ�Ÿ��ϱ�
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
				// ������
				SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
				// �÷��̾� �������� ���� �߻�
				SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
				SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;;
				SimpleMath::Vector3 direction = playerPos - origin;
				origin += direction * 0.15;
				// �ִ�Ÿ��ϱ�
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
		// ���ݾִϸ��̼��� ���������� ���ߵ�
		if (m_attackPassingTime >= m_attackCoolTime)
		{
			// TODO : �����߿� �����̳�?
			m_moveSpeed = 0.f;

			m_passingTime += dTime;

			if (m_passingTime >= m_attackSpeed)
			{
				// �ִϸ��̼�
				m_model->GetComponent<MeshRenderer>()->PlayAnimationOnce(0);

				// ������
				SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
				// �÷��̾� �������� ���� �߻�
				SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
				// TODO : ������ ��� ����ϴ� �ϵ��ڵ�
				SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;;
				SimpleMath::Vector3 direction = playerPos - origin;
				origin += direction * 0.15;
				// �ִ�Ÿ��ϱ�
				float maxDistance = m_attackRange[m_awakenedLevel];

				Collision* hit = nullptr;

				/// Attack ����
				/// ��� ���̴� ä���� ���带 �ϴ� ����
				if (!m_isAttack)
				{
					SoundManager::GetInstance()->StopSound(SoundManager::GetInstance()->GetBlindChannel());
					m_isAttack = true;
					m_isChase = false;
					m_isWalk = false;
				}

				m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit);

				// �������µ� �÷��̾ ������ �ٽ� �Ѿư���
				if (hit)
				{
					if (hit->GetOwner()->GetName() == "Player")
					{
						// ���� ����
						SoundManager::GetInstance()->PlayBlind(eSOUNDKIND::fBlindAttack);
						//std::cout << "Attack" << std::endl;

						hit->GetOwner()->GetComponent<PlayerComponent>()
							->SetHp(m_player->GetComponent<PlayerComponent>()->GetHp() - m_damage);
						SoundManager::GetInstance()->PlaySFX(eSOUNDKIND::fPhit);
						// ������
						SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
						// �÷��̾� �������� ���� �߻�
						SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
						SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;
						SimpleMath::Vector3 direction = playerPos - origin;
						origin += direction * 0.15;
						// �ִ�Ÿ��ϱ�
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
			// ������
			SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
			// �÷��̾� �������� ���� �߻�
			SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
			SimpleMath::Vector3 origin = enemyPos + (playerPos - enemyPos) * 0.1f;
			SimpleMath::Vector3 direction = playerPos - origin;
			origin += direction * 0.15;
			// �ִ�Ÿ��ϱ�
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
		// �ִϸ��̼�
		m_model->GetComponent<MeshRenderer>()->SetAnimationState(1);

		/// ���� �ϸ� �Ͻ� ����
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

		// ��� ����
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

	// ȸ����
	float rot = 0.f;

	// ����
	if (m_dirToNextPos.x >= 1.f)
	{
		rot = -90.f * 3.141592f / 180.f;
	}

	// ������
	else if (m_dirToNextPos.x <= -1.f)
	{
		rot = 90.f * 3.141592f / 180.f;
	}

	// ��
	else if (m_dirToNextPos.z >= 1.f)
	{
		rot = 180.f * 3.141592f / 180.f;
	}

	// ��
	else if (m_dirToNextPos.z <= -1.f)
	{
		rot = 0.f * 3.141592f / 180.f;
	}

	if (m_enemyState == EnemyState::Attack)
	{
		// �� �༮�� �»����� �޶�Ծ ���� ���
		SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
		SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();
		rot = -atan2((playerPos.z - enemyPos.z), (playerPos.x - enemyPos.x)) - 90.f * 3.141592f / 180.f;
	}
	m_pOwner->GetComponent<Transform>()->SetRotation({ 0.f,rot,0.f });

}

void Blind::LateUpdate(float dTime)
{
	// ����� �ٲ� ���¸��� �Ѿ�� ���𰡸�..?


	
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
	// ������
// 	SimpleMath::Vector3 enemyPos = m_pOwner->GetComponent<Transform>()->GetPosition();
// 	// �÷��̾� �������� ���� �߻�
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
