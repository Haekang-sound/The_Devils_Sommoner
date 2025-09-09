#pragma once
#include "Scene.h"
#include "SoundManager.h"

class CollisionDetectManager;
class GameManager;

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	// Scene의 기본정보를 편집한다.
	virtual void EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager) override;
	virtual void Awake() override;
	virtual void Start() override;			// scene이 시작될 때 일어나는 행동을 한다.
	void FixedUpdate(float dTime) override;	// Scene을(를) 통해 상속됨
	virtual void Update(float dTime) override;		// scene에 존재하는 오브젝트들을 일괄 Update한다.
	virtual void LateUpdate(float dTime) override;	// 정리를 위한 두번째 업데이트
	virtual void Render() override;					// scene에 존재하는 오브젝트들을 일괄 Render한다.
	virtual void End() override;					// scene의 오브젝트들을 해제한다.
	virtual void EndLayer(unsigned int _layer) override;

	// Scene을(를) 통해 상속됨
	SceneNumber GetSceneNum() override;

public:
	// 나의 씬넘버
	SceneNumber m_myNum = SceneNumber::Title;

	// 채널 뱉기
	Channel* GetChannel(int index);

private:
	// Test
	//CollisionDetectManager* m_detectManager;
	//GameObject* obj1;
	//GameObject* obj2;
	//
	GameManager* m_gameManager = nullptr;
	Channel* m_channel = nullptr;
	vector<Channel*> m_channels = {};
};

