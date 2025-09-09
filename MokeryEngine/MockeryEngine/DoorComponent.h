#pragma once
#include "InteractiveObject.h"

using namespace DirectX;

class GameObject;

enum class DoorState
{
	Close,
	Open,
};

class DoorComponent : public InteractiveObject
{
	using Super = InteractiveObject;

public:
	DoorComponent();
	virtual ~DoorComponent();

public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

public:
	void Interact() override;
	void InteractAddTime(float dTime) override;

	void SetDoorObject(GameObject* door);

	const DoorState& GetDoorState();

	void SetDoorModelObject(GameObject* door);

private:
	GameObject* m_door;
	GameObject* m_doorModel;

	DoorState m_doorState;

	float m_doorSpeed;
	bool isActivated;

	float m_maxAngle;
	float m_maxAngleToRadian;
	//GameObject* m_DoorFrame;
};

