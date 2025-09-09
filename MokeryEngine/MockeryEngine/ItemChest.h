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
	// 열린 순간만을 확인하기 위한 bool변수
	bool m_isOpen;
	bool m_isDisabled;
	bool m_forSound;

	/// 아이템 사용 여부를 확인 하기 위한 get 
	/// 작성자 : 오해강
public:
	bool GetisOpen()const { return m_isOpen; }
	bool GetisActivated()const { return m_isActivated; }
	void SetisClose() { m_isOpen = false; }
	ItemList GetItemType() const { return m_itemType; }
};