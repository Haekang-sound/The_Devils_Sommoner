#pragma once
#include "Scene.h"


class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();
	// Scene을(를) 통해 상속됨
	virtual void EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager) override;//, InputManager* inputManger) override;
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void End() override;
	virtual void EndLayer(unsigned int _layer) override;

	// Scene을(를) 통해 상속됨
	SceneNumber GetSceneNum() override;
	
public:
	// 나의 씬넘버
	SceneNumber m_myNum = SceneNumber::Test;

	
};