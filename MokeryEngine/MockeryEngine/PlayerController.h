#pragma once
#include "Component.h"

class InputManager;
class Transform;

class PlayerController : public Component
{
public:
	// Component을(를) 통해 상속됨
	PlayerController();
	virtual ~PlayerController();

	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

	void Move(float dTime);

	// 뭐임 이거
	SimpleMath::Matrix m_View;
	RenderMatrix44 m_RenderView;
private:
	InputManager* m_inputmanager;

private:
	HCURSOR hCursor;
	Transform* m_transform;
	SimpleMath::Vector3 m_pos;
	SimpleMath::Vector3 m_rot;

	float maxSpeed = 0.f;
	float m_moveSpeed;

	int m_fov;

	float speedX;
	float speedY;
	float speedZ;
	float rotSpeed;

	bool isControl = true;

	bool isWalk = false;
	bool isRun = false;

	SimpleMath::Vector3 m_dir;
	float m_velocity = 0.f;
};

