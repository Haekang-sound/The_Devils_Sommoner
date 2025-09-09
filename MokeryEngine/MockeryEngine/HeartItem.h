#pragma once
#include "Item.h"

class GameObject;
class Transform;

class HeartItem : public Item
{
public:
	HeartItem();
	virtual ~HeartItem();

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	void Select() override;
	void UnSelect() override;
	virtual void Act(GameObject* player) override;

protected:
	void FindNextAltar();

public:
	void SetHeartModelObject(GameObject* heartModel);

	void SetHeartBeatCycle(float time);
	// ���� ��ǥ�� ���� ������ �������ش�.
	void SetHeartAltar(GameObject* heartAltar);
	/// �Ÿ��� ���� ���� �ڵ� ����Ŭ �ӵ��� �������ش�.
	void UpdateSpeedByDistanceValue();

private:
	GameObject* m_modelObject;
	Transform* m_heartTransform;
	int m_altarCount;
	bool m_isActivated;
	bool m_isDisturbing;

	float m_heartBeatSpeed;
	int m_inverseNum;

	float m_maxSize;
	float m_minSize;

private:
	// �Ÿ� ������ ���� �ӵ� ������ �ٸ��� �Ѵ�
	//const SimpleMath::Vector3& RelativePosition()

	float m_distance;
	float m_maxDistance;
	float m_ratio;
	Transform* m_transform;

	SimpleMath::Vector3 m_nowPosition;
	SimpleMath::Vector3 m_targetPosition;

private:
	// �Ʒ����ʹ� ����

	SimpleMath::Vector3 m_originScale;

	// ���� ���� �ڵ� �ֱ�
	float m_originalHeartBeatCycleTime;
	// ���� �ڵ� �ֱ�
	float m_heartBeatCycleTime;
	// ���� �ð�
	float m_currentHeartBeatTime;
	bool m_onHeartBeat;
};

