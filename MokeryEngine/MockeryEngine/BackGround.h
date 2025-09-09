#pragma once
#include "Component.h"
#include "EngineResourceManager.h"
#include "GameObject.h"
#include "AudioComponent.h"

class GameObject;
class EngineResourceManager;
class InputManager;
class BackGround : public Component
{
public:
	BackGround();
	virtual ~BackGround();

	virtual void Start() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

public:
	EngineResourceManager* m_resourceManager;
	InputManager* m_inputmanager;

	// Component을(를) 통해 상속됨
	void FixedUpdate(float dTime) override;
};

