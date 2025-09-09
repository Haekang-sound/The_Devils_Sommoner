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
	Stun,	// �׳� ���� ���¸� ����ϰ���
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

	// Component��(��) ���� ��ӵ�
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollisionEnter(Collision* collision) override;
	virtual void OnCollisionStay(Collision* collision) override;
	virtual void OnCollisionExit(Collision* collision) override;

	// �ʿ��Ѱ� ����
	void SetHp(float _hp) { m_hp = _hp; }
	float GetHp() { return m_hp; }

	float GetDetectRange() { return m_detectRange[m_awakenedLevel]; }
	// ���� �͵�

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
	// �迭�� ���� �������� �����Ѵ�. ���� �����ǵ� �ٲ��.
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
	// ���� ���������� �����Ͽ������� �˻��Ѵ�.
	bool CheckNextTile();
	// ���ο� ���� �������� ���ϰ� ������ �����Ѵ�.
	void FindNextTile();
	// ������ �������� ������ ���� ã�� �����Ѵ�. �̴� Astar�� �̿��Ѵ�.
	void FindPath();

	// �÷��̾��� �������� Ÿ���� ���������� �ٲ۴�.
	PathPos TransPlayerPosToTilePos();

	// �� �������� Ÿ���� �������� �ٲ۴�.
	PathPos TransPosToTilePos();

	// ���� ��ȣ�ۿ�. true�� ���� ���� ���� ���, false �� ���� ���� ���� ���
	bool InteractWithDoor(float dTime);

protected:
	float m_hp;
	float m_damage;
	float m_attackSpeed;
	float m_attackCoolTime;
	float m_moveSpeed;
	std::vector<float>  m_walkSpeed;
	std::vector<float>  m_chaseSpeed;
	// ���ݹ���
	std::vector<float>  m_attackRange;
	// �߰�����
	std::vector<float>  m_detectRange;
	// �þ߹���
	std::vector<float>  m_sightRange;

	// Į �¾Ҵ��� �ƴ���
	bool m_isHitByKnife;
	bool m_isStart;
	bool m_isKnifeSound;

	float m_passingTime;
	float m_attackPassingTime;
	float m_stunPassingTime;

	EnemyState m_enemyState;
	EnemyState m_beforeState;
	EnemyState m_nextState;


	// ��������
	static int m_awakenedLevel;

	std::vector<GameObject*> m_altar;

	// ���� ����
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
	// ���� ã���� �����Ѵ�.
	bool m_onFindDoor;

};
