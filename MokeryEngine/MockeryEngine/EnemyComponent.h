#pragma once

#include "Component.h"
#include "CommonStructs.h"
#include "ModelEnum.h"

enum class EnemyState
{
	Interact,
	Walk,
	Chase,
	Attack,
	Stun,	// 그냥 스턴 상태를 사용하겠음
	Dead,
	NONE,
};

class AStarPathFindComponent;
class Transform;
class EngineObjectManager;

class EnemyComponent : public Component
{
public:
	EnemyComponent();
	virtual ~EnemyComponent();

	// Component을(를) 통해 상속됨
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollisionEnter(Collision* collision) override;
	virtual void OnCollisionStay(Collision* collision) override;
	virtual void OnCollisionExit(Collision* collision) override;

	// 필요한가 싶음
	void SetHp(float _hp) { m_hp = _hp; }
	float GetHp() { return m_hp; }

	float GetDetectRange() { return m_detectRange[m_awakenedLevel]; }
	// 위에 것들

	bool PlayerTracker(float _range, DirectX::SimpleMath::Vector3 _enemyPos, DirectX::SimpleMath::Vector3 _playerPos);
	void SetEnemyStun()
	{
		//std::cout << "Stun" << std::endl;
		m_enemyState = EnemyState::Stun;
		m_nextState = EnemyState::Stun;
	}

	void SetEnemyKnifeHit(bool isHit) { m_isHitByKnife = isHit; }

	void SetStartPos(int y, int x);

protected:
	// 배열의 시작 포지션을 설정한다. 실제 포지션도 바뀐다.
	void SetStartPos(PathPos pos);

public:
	void SetPlayerObject(GameObject* player);
	void SetAltarObject(std::vector<GameObject*> altar);
	void SetEngineObjectManager(EngineObjectManager* engineObjectManager);
	void SetObjectVectorTarget(std::vector<GameObject*>* objectVector);
	void SetEnemyModel(EnumModel modelnum);
	GameObject* GetEnemyModel() { return m_model; }
	EnemyState GetEnemyState() { return m_enemyState; }

protected:
	// 다음 목적지까지 도달하였는지를 검사한다.
	bool CheckNextTile();
	// 새로운 다음 목적지를 구하고 방향을 설정한다.
	void FindNextTile();
	// 지정한 목적지가 있으면 길을 찾아 저장한다. 이는 Astar를 이용한다.
	void FindPath();

	// 플레이어의 포지션을 타일의 포지션으로 바꾼다.
	PathPos TransPlayerPosToTilePos();

	// 내 포지션을 타일의 포지션을 바꾼다.
	PathPos TransPosToTilePos();

	// 문과 상호작용. true일 경우는 문이 있을 경우, false 일 경우는 문이 없을 경우
	bool InteractWithDoor(float dTime);

protected:
	float m_hp;
	float m_damage;
	float m_attackSpeed;
	float m_attackCoolTime;
	float m_moveSpeed;
	std::vector<float>  m_walkSpeed;
	std::vector<float>  m_chaseSpeed;
	// 공격범위
	std::vector<float>  m_attackRange;
	// 발각범위
	std::vector<float>  m_detectRange;
	// 시야범위
	std::vector<float>  m_sightRange;

	// 칼 맞았는지 아닌지
	bool m_isHitByKnife;
	bool m_isStart;
	bool m_isKnifeSound;

	float m_passingTime;
	float m_attackPassingTime;
	float m_stunPassingTime;

	EnemyState m_enemyState;
	EnemyState m_beforeState;
	EnemyState m_nextState;


	// 각성레벨
	static int m_awakenedLevel;

	std::vector<GameObject*> m_altar;

	// 사운드 관련
	bool m_isWalk;
	bool m_isChase;
	bool m_isAttack;
	bool m_isDead;
	bool m_isChasing;

	BoundingBox m_knifeCheckBox;

protected:
	AStarPathFindComponent* m_astar;
	Transform* m_transform;

	SimpleMath::Vector3 m_nextPos;
	SimpleMath::Vector3 m_dirToNextPos;
	PathPos m_startPathPos;
	PathPos m_destPos;

protected:
	GameObject* m_player;
	GameObject* m_model;
	float m_tileSize;
	EngineObjectManager* m_objManager;
	std::vector<GameObject*>* m_objectVector;

private:
	float m_interactTime;
	float m_needToInteractTile;

protected:
	// 문을 찾을기 결정한다.
	bool m_onFindDoor;

};
