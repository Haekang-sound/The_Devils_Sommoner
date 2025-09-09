#pragma once
#include "Scene.h"

class CollisionDetectManager;
class GameManager;
class Button;
class SpriteRenderer;

class IntroScene : public Scene
{
public:
    IntroScene();
    virtual ~IntroScene();
    // Scene을(를) 통해 상속됨
    virtual void EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager) override;
    virtual void Awake() override;
    virtual void Start() override;
    virtual void FixedUpdate(float dTime) override;
    virtual void Update(float dTime) override;
    virtual void LateUpdate(float dTime) override;
    virtual void Render() override;
    virtual void End() override;
    virtual void EndLayer(unsigned int _layer) override;
    SceneNumber GetSceneNum() override;

public:
	// 나의 씬넘버
	SceneNumber m_myNum = SceneNumber::Intro;
    Button* m_helpButton = nullptr;
    SpriteRenderer* m_helpSprite = nullptr;

private:
    GameManager* m_gameManager = nullptr;
};

