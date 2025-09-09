#pragma once
#include "Scene.h"
class EngineResourceManager;
class EngineObjectManager;
class CollisionDetectManager;
class PhysicsManager;
class TimeManager;
class SoundManager;
class ID3DRenderer;

/// <summary>
/// Scene�� �����ϰ� �ҷ�����
/// �����ϴ� �Ŵ���
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init(TimeManager* timeManager);//, InputManager* inputManager);
	void LoadResource();
	void FixedUpdate(float dTime);
	void Update(float dTime);
	void LateUpdate(float dTime);
	void Render();

	void Finalize();

	/// get/set
public:
	ID3DRenderer* GetRenderer() const { return m_renderer; }
	void SetRenderer(ID3DRenderer* val) { m_renderer = val; }	// MeshRendererComponent

public:
	void ChangeScene(SceneNumber seceneName);	// scene�� �����Ѵ�.

private:
	void AddScene(SceneNumber sceneName);		// scene�� �߰��Ѵ�. 

	// scene���ο��� �����ؼ� scene�� ����ɼ��ִ� ��� ����� ���� �̵��Ѵ�.
	void EndScene();							// scene�� �����Ѵ�.

	void SetCurrentScene(SceneNumber seceneName);

	/// scene�Ŵ����� �ʼ������ �����
private:
	Scene* m_currentScene;	// ���� Scene
	Scene* m_newScene;		// ������ ���� �ӽú���

	// Scene�� ������ �����ؼ� �̸����� �ҷ��´�.
	std::unordered_map<SceneNumber, Scene*> m_sceneMap;
	
private:
	//KSL* m_soundKSL;
	//SoundManager* m_soundManager;
 	EngineResourceManager* m_resourceManager;
 	EngineObjectManager* m_objManager;
	CollisionDetectManager* m_collisionDetectManager;
	PhysicsManager* m_physicsManager;
	//InputManager* m_inputManager;
	TimeManager* m_timeManager;
	ID3DRenderer* m_renderer;

};