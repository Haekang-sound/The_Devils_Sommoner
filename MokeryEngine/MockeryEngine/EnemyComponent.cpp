#include "pch.h"
#include "EnemyComponent.h"
#include "Collision.h"
#include "GameObject.h"
#include "RayComponent.h"
#include "Transform.h"
#include "PlayerComponent.h"
#include "AStarPathFindComponent.h"
#include "Transform.h"
#include "GameManager.h"
#include "RayComponent.h"
#include "InteractiveObject.h"
#include "DoorComponent.h"
#include "DemonAltarComponent.h"
#include "MeshRenderer.h"
#include "EngineObjectManager.h"
#include "SoundManager.h"

int EnemyComponent::m_awakenedLevel = 0;

/// <summary>
/// 적에 관한 정보
/// </summary>
EnemyComponent::EnemyComponent()
	: m_hp(0.f), m_walkSpeed{ 0.f, }
	, m_damage(0.f), m_attackSpeed(0.f), m_chaseSpeed{ 0.f, }, m_passingTime(0.f), m_attackPassingTime(0.f)
	, m_attackRange{ 0.f, }, m_detectRange{ 0.f, }, m_sightRange{ 0.f, }
	, m_isHitByKnife(false), m_moveSpeed(0.f)
	, m_enemyState(EnemyState::NONE), m_nextState(EnemyState::NONE)
	, m_astar(nullptr)
	, m_transform(nullptr)
	, m_nextPos()
	, m_dirToNextPos()
	, m_startPathPos()
	, m_destPos()
	, m_player(nullptr)
	, m_tileSize(0.f)
	, m_interactTime(0.f)
	, m_needToInteractTile(1.f)
	, m_isWalk(false)
	, m_isChase(false)
	, m_isAttack(false)
	, m_isDead(false)
	, m_isChasing(false)
	, m_isStart(false)
	, m_isKnifeSound(false)
	, m_stunPassingTime(0.f)
{

}

EnemyComponent::~EnemyComponent()
{

}

void EnemyComponent::Start()
{
	m_player = GameManager::GetInstance()->GetPlayerObject();


	m_astar = m_pOwner->GetComponent<AStarPathFindComponent>();
	m_transform = m_pOwner->GetComponent<Transform>();

	m_tileSize = m_astar->GetTileSize();

	m_astar->SetStartPos(m_startPathPos);
	SetStartPos(m_startPathPos);
	FindPath();
	FindNextTile();
}

void EnemyComponent::FixedUpdate(float dTime)
{

}

void EnemyComponent::Update(float dTime)
{
	//if (m_player->GetComponent<PlayerComponent>()->GetHp() <= 0.f)
	//{
	//	m_nextState = EnemyState::NONE;
	//	m_enemyState = EnemyState::NONE;
	//}
}

void EnemyComponent::LateUpdate(float dTime)
{

}

void EnemyComponent::Render()
{
// 	BoundingBox m_boundingBox;
// 	m_boundingBox.Center = m_pOwner->GetComponent<Transform>()->GetPosition();
// 	m_boundingBox.Extents = { 1.f,1.f,1.f };
// 
// 	m_renderer->DrawDebugingBoundingBox({ m_boundingBox.Center.x, m_boundingBox.Center.y, m_boundingBox.Center.z },
// 		{ m_boundingBox.Extents.x, m_boundingBox.Extents.y, m_boundingBox.Extents.z },
// 		{ 0.f,0.f,0.f,0.f }, { 1.f,1.f,1.f,1.f }
// 	);

}

void EnemyComponent::Release()
{
	m_awakenedLevel = 0;
}

void EnemyComponent::OnCollisionEnter(Collision* collision)
{

}

void EnemyComponent::OnCollisionStay(Collision* collision)
{

}

void EnemyComponent::OnCollisionExit(Collision* collision)
{

}

// 플레이어와 적 사이의 거리 비교
bool EnemyComponent::PlayerTracker(float _range, DirectX::SimpleMath::Vector3 _enemyPos, DirectX::SimpleMath::Vector3 _playerPos)
{
	float m_Distance = sqrt(pow(_enemyPos.x - _playerPos.x, 2.f) + pow(_enemyPos.z - _playerPos.z, 2.f));

	if (m_Distance <= _range)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EnemyComponent::CheckNextTile()
{
	SimpleMath::Vector3 currentPos = m_transform->GetPosition();

	float offset = 0.05f;
	if (fabs(m_nextPos.x - currentPos.x) < offset
		&& fabs(m_nextPos.y - currentPos.y) < offset
		&& fabs(m_nextPos.z - currentPos.z) < offset)
	{
		m_transform->SetPosition(m_nextPos);
		return true;
	}

	return false;
}

void EnemyComponent::FindNextTile()
{
	TileInfo nextTileInfo = m_astar->GetNextPos(m_transform->GetPosition());
	m_nextPos = nextTileInfo.tilePos;
	m_dirToNextPos = m_nextPos - m_transform->GetPosition();
	m_dirToNextPos.Normalize();

	// 만약 문이라면 스테이트 변경 -> 수정. 문이라면 문 앞에 갈떄까지 문을 찾을 ray를 사용하기 시작
	if (nextTileInfo.tileType == TileType::Door_1
		|| nextTileInfo.tileType == TileType::Door_2
		)
	{
		//m_enemyState = EnemyState::Interact;
		m_onFindDoor = true;
	}
	else
	{
		m_onFindDoor = false;
	}
}

void EnemyComponent::FindPath()
{
	m_astar->AstarPathFinding();
}

PathPos EnemyComponent::TransPlayerPosToTilePos()
{
	SimpleMath::Vector3 playerPos = m_player->GetComponent<Transform>()->GetPosition();

	float posX = playerPos.x / m_tileSize;
	float posZ = playerPos.z / m_tileSize;
	//std::cout << "TransPlayerToTilePos : " << (int)posX << ", " << (int)posZ << std::endl;

	return { static_cast<int>(posX), static_cast<int>(posZ) };
}

PathPos EnemyComponent::TransPosToTilePos()
{
	SimpleMath::Vector3 pos = m_transform->GetPosition();

	float posX = pos.x / m_tileSize;
	float posZ = pos.z / m_tileSize;
	//std::cout << "TransPosToTilePos : " << (int)posX << ", " << (int)posZ << std::endl;

	return { static_cast<int>(posX), static_cast<int>(posZ) };
}

bool EnemyComponent::InteractWithDoor(float dTime)
{
	SimpleMath::Vector3 origin = m_pOwner->GetComponent<Transform>()->GetPosition();
	//SimpleMath::Vector3 direction = m_pOwner->GetComponent<Transform>()->GetForward();
	SimpleMath::Vector3 direction = m_dirToNextPos;

	// TEMP : 여기 하드코딩임. ray가 내 콜라이더와 겹칠 수 있으니 혹시나 검출이 안될 경우 여기를 보라!
	origin += direction * 0.4f;
	float maxDistance = 0.3f;
	Collision* hit = nullptr;
	m_pOwner->GetComponent<RayComponent>()->Ray(origin, direction, maxDistance, &hit);

	if (hit)
	{
		// 문인지
		if (DoorComponent* obj = hit->GetOwner()->GetComponent<DoorComponent>())
		{
			m_interactTime += dTime;
			// 상호작용에 필요한 시간이 지난 후
			if (m_interactTime >= m_needToInteractTile)
			{
				// 문이 닫혀 있을 경우만 연다!
				if (obj->GetDoorState() == DoorState::Close)
				{
					obj->Interact();
					//std::cout << "Enemy Interact" << std::endl;
				}
			}
			return true;
		}
	}

	// 문이 없을 경우 (아직 문을 못찾았거나 이미 열린 경우, 또는 플레이어가 도중에 연 경우)
	m_interactTime = 0.f;
	return false;
}

void EnemyComponent::SetStartPos(PathPos tilePos)
{
	m_startPathPos = tilePos;
	SimpleMath::Vector3 currentPos = m_transform->GetPosition();

	currentPos.x = tilePos.y * m_astar->GetTileSize();
	currentPos.z = tilePos.x * m_astar->GetTileSize();

	m_transform->SetPosition(currentPos);
}

void EnemyComponent::SetStartPos(int y, int x)
{
	m_startPathPos = { y,x };
}

void EnemyComponent::SetPlayerObject(GameObject* player)
{
	m_player = player;
}

void EnemyComponent::SetAltarObject(std::vector<GameObject*> altar)
{
	m_altar = altar;
}

void EnemyComponent::SetEngineObjectManager(EngineObjectManager* engineObjectManager)
{
	m_objManager = engineObjectManager;
}

void EnemyComponent::SetObjectVectorTarget(std::vector<GameObject*>* objectVector)
{
	m_objectVector = objectVector;
}

void EnemyComponent::SetEnemyModel(EnumModel modelnum)
{
	//GameObject* object;
	m_model = m_objManager->CreateObject();
	m_model->AddComponent<MeshRenderer>();
	m_model->GetComponent<MeshRenderer>()->SetAssetNum(static_cast<int>(modelnum));
	m_model->GetComponent<MeshRenderer>()->CreateModel();
	m_model->GetComponent<Transform>()->SetLocalScale({ 0.0034f,0.0034f,0.0034f });
	m_model->GetComponent<Transform>()->SetLocalPosition({ 0.f,-1.0f,0.f });
	m_model->SetParentByGameObject(m_pOwner);
	m_model->GetComponent<MeshRenderer>()->SetThisIsANIMATION();

	m_objectVector->push_back(m_model);
}
