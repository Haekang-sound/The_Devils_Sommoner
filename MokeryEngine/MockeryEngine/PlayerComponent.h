#pragma once

#include "Component.h"

class Item;
class Inventory;
class CameraComponent;

struct PlayerInfo
{
	float _Hp;
	float _WalkSpeed;
	float _RunSpeed;
};


class PlayerComponent : public Component
{
public:
	PlayerComponent();
	~PlayerComponent();

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


	void SetHp(float _hp) { m_hp = _hp; }
	float GetHp() { return m_hp; }

	float GetStamina() const { return m_stamina; }

	void SetMoveSpeed(float _moveSpeed) { m_moveSpeed = _moveSpeed; }
	void SetMoveSpeed(float walkSpeed, float runSpeed) 
	{ 
		m_walkSpeed = walkSpeed;
		m_runSpeed =runSpeed;
	}
	float GetMoveSpeed() { return m_moveSpeed; }

	DirectX::SimpleMath::Vector3 GetPlayerPos() { return m_pos; }

	void Interact(GameObject* _object);

	void SethaveHeart(bool haveHeart) { m_haveHeart = haveHeart; }
	bool GethaveHeart() { return m_haveHeart; }
	bool GetholdHeart() { return m_holdHeart; }

	void SetGameStart(bool isGameStarted) { m_isGameStarted = isGameStarted; }
	bool GetGameStart() { return m_isGameStarted; }

	void SetItemState(float itemState) { m_itemState = itemState; }
	float GetItemState() { return m_itemState; }

	bool GetIsKnifeReady()const { return m_isKnifeReady; }

public:
	void UseSelectedItem();
	void SelectItem(const int& index);

private:
	void CheckInteractiveObject(float dTime);

private:
	float m_hp;
	float m_stamina;
	float m_maxStamina;
	float m_minStamina;
	float m_moveSpeed;
	float m_walkSpeed;
	float m_runSpeed;

	bool m_isRunning;
	bool m_isInteracting;
	bool m_isBeforeInteracting;
	float m_itemState;

	bool m_isHandedKnife;
	bool m_isHandedItem;

	DirectX::SimpleMath::Vector3 m_pos;

private:
	Item* m_selectedItem;
	Inventory* m_inventory;
	CameraComponent* m_camera;

public:
	void OnKnife();
	void OnHeart();

private:
	// �׳� �������� �Ҹ��� ���� �߰��� �����ϰڴ�
	bool m_haveKnife;
	bool m_haveHeart;
	bool m_holdHeart;

	float m_passingTime;
	float m_staminaCoolTime;
	float m_knifeCoolTime;

	bool m_isGameStarted;

	bool m_isStaminaZero;
	bool m_isExhausted;

	bool m_isKnifeReady;

	int m_fov;

	// �������� ������ �ִϸ��̼��� ������ �ʰ� �ϱ� ���� ����
	float m_knifeAnimationFinishTime;
	float m_knifeAnimationCurrentTime;
	bool m_isKnifeAnimationPlaying;
};