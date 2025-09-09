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
	// 현재 목표인 심장 제단을 세팅해준다.
	void SetHeartAltar(GameObject* heartAltar);
	/// 거리에 따라 심장 박동 사이클 속도를 조절해준다.
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
	// 거리 비율에 따라 속도 조절을 다르게 한다
	//const SimpleMath::Vector3& RelativePosition()

	float m_distance;
	float m_maxDistance;
	float m_ratio;
	Transform* m_transform;

	SimpleMath::Vector3 m_nowPosition;
	SimpleMath::Vector3 m_targetPosition;

private:
	// 아래부터는 심장

	SimpleMath::Vector3 m_originScale;

	// 원래 심장 박동 주기
	float m_originalHeartBeatCycleTime;
	// 심장 박동 주기
	float m_heartBeatCycleTime;
	// 현재 시간
	float m_currentHeartBeatTime;
	bool m_onHeartBeat;
};

