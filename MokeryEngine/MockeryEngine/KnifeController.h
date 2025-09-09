#pragma once
#include "Component.h"
#include "framework.h"

enum class KnifeSate
{
	IDLE,
	AIM,
	SHOOT,
	WAIT,
};

class CameraComponent;
class Transform;
/// <summary>
/// �������� ��Ʈ���ϴ� ��Ʈ�ѷ�
/// </summary>
class KnifeController : public Component
{
public:
	KnifeController();
	// Component��(��) ���� ��ӵ�
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	void SetCamera(CameraComponent* camera);

private:
	void StateAim();
	void StateIdle();
	void StateShoot();

private:
	void ShootKnife();
	void SetKnifeTransform();

private:
	KnifeSate m_state;

private:
	CameraComponent* m_camera;
	Transform* m_transform;

	SimpleMath::Vector3 m_parentPos;
	SimpleMath::Vector3 m_parentRot;
	SimpleMath::Vector3 m_parentfoward;

	bool isSet;
	bool isShoot;

};

