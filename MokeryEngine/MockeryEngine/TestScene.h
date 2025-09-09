#pragma once
#include "Scene.h"


class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();
	// Scene��(��) ���� ��ӵ�
	virtual void EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager) override;//, InputManager* inputManger) override;
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void End() override;
	virtual void EndLayer(unsigned int _layer) override;

	// Scene��(��) ���� ��ӵ�
	SceneNumber GetSceneNum() override;
	
public:
	// ���� ���ѹ�
	SceneNumber m_myNum = SceneNumber::Test;

	
};