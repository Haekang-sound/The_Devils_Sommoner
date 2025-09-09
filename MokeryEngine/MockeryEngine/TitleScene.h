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

	// Scene�� �⺻������ �����Ѵ�.
	virtual void EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager) override;
	virtual void Awake() override;
	virtual void Start() override;			// scene�� ���۵� �� �Ͼ�� �ൿ�� �Ѵ�.
	void FixedUpdate(float dTime) override;	// Scene��(��) ���� ��ӵ�
	virtual void Update(float dTime) override;		// scene�� �����ϴ� ������Ʈ���� �ϰ� Update�Ѵ�.
	virtual void LateUpdate(float dTime) override;	// ������ ���� �ι�° ������Ʈ
	virtual void Render() override;					// scene�� �����ϴ� ������Ʈ���� �ϰ� Render�Ѵ�.
	virtual void End() override;					// scene�� ������Ʈ���� �����Ѵ�.
	virtual void EndLayer(unsigned int _layer) override;

	// Scene��(��) ���� ��ӵ�
	SceneNumber GetSceneNum() override;

public:
	// ���� ���ѹ�
	SceneNumber m_myNum = SceneNumber::Title;

	// ä�� ���
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

