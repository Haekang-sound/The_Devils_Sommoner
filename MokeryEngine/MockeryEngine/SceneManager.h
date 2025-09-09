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
/// Scene을 저장하고 불러오는
/// 관리하는 매니저
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
	void ChangeScene(SceneNumber seceneName);	// scene을 변경한다.

private:
	void AddScene(SceneNumber sceneName);		// scene을 추가한다. 

	// scene내부에서 동작해서 scene이 변경될수있는 모든 경우의 수로 이동한다.
	void EndScene();							// scene을 종료한다.

	void SetCurrentScene(SceneNumber seceneName);

	/// scene매니저의 필수기능을 담당함
private:
	Scene* m_currentScene;	// 현재 Scene
	Scene* m_newScene;		// 생성을 위한 임시변수

	// Scene을 맵으로 저장해서 이름으로 불러온다.
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