#pragma once
#include "InteractiveObject.h"

class PlayerComponent;
class Timer;

enum class ItemList
{
	Heal,
	xRay,
	SpeedUp,
	SpeedDown,
	LostTime,
	//NONE,
};


class ItemChest : public InteractiveObject
{
	using Super = InteractiveObject;

public:
	ItemChest();
	virtual ~ItemChest();

public:
	void Awake() override;
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	virtual void InteractAddTime(float dTime) override;
	virtual void Interact() override;

public:
	void SetPlayer(PlayerComponent* _player) { m_player = _player; }
	void SetItemChestModelObject(GameObject* model);
	void SetRandomItemType();

private:
	ItemList m_itemType;
	bool m_isActivated;
	PlayerComponent* m_player;
	Timer* m_timer;
	float m_passingTime;
	static float m_staticpassingTime;
	GameObject* m_itemChestModel;
	// ���� �������� Ȯ���ϱ� ���� bool����
	bool m_isOpen;
	bool m_isDisabled;
	bool m_forSound;

	/// ������ ��� ���θ� Ȯ�� �ϱ� ���� get 
	/// �ۼ��� : ���ذ�
public:
	bool GetisOpen()const { return m_isOpen; }
	bool GetisActivated()const { return m_isActivated; }
	void SetisClose() { m_isOpen = false; }
	ItemList GetItemType() const { return m_itemType; }
};