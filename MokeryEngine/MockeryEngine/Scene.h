#pragma once
#include "framework.h"
#include "SceneEnum.h"

/// <summary>
/// 오브젝트들이 
/// 올라가고 상호작용하는 공간
/// </summary>

class SceneManager;
class SoundManager;
class EngineResourceManager;
class EngineObjectManager;
class TimeManager;
class InputManager;
class CollisionDetectManager;
class PhysicsManager;
class GameObject;
class ID3DRenderer;

class Scene
{
public:
	virtual ~Scene() {};

	// Scene의 기본정보를 편집한다.
	virtual void EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager) abstract; // , InputManager* inputManger) abstract;	// scene이 시작될 때 일어나는 행동을 한다.
	
	virtual void Awake() abstract;
	virtual void Start() abstract;

	virtual void FixedUpdate(float dTime) abstract;

	// scene에 존재하는 오브젝트들을 일괄 Update한다.
	virtual void Update(float dTime) abstract;
	// 정리를 위한 두번째 업데이트
	virtual void LateUpdate(float dTime) abstract;
	// scene에 존재하는 오브젝트들을 일괄 Render한다.
	virtual void Render() abstract;
	// scene의 모든 오브젝트들을 해제한다.
	virtual void End() abstract;
	// Scene의 레이이어에 따라 오브젝트들을 삭제한다.
	virtual void EndLayer(unsigned int _layer) abstract;

	/// <summary>
	/// Get/Set
	/// </summary>
public:
	Scene* GetScene(){ return this; }

	ID3DRenderer* GetRenderer() const { return m_renderer; }
	void SetRenderer(ID3DRenderer* val) { m_renderer = val; }

	virtual SceneNumber GetSceneNum()abstract;

	// scene변경할 때 필요함
	SceneManager* GetSceneManger() const { return m_sceneManager; }
	void SetSceneManger(SceneManager* val) { m_sceneManager = val; }

protected:
	// scene에 존재하는 오브젝트들
	std::vector<GameObject*> m_objects{};

	// 오브젝트 생성을 위한 임시변수
	GameObject* m_object = nullptr;

	EngineObjectManager* m_objManager = nullptr;
	EngineResourceManager* m_resourceManager = nullptr;
	TimeManager* m_timeManager = nullptr;
	InputManager* m_inputManager = nullptr;
	SceneManager* m_sceneManager = nullptr;
	/*SoundManager* m_soundManager = nullptr;
	SoundManager::getInstance() = nullptr;*/

	// 오디오 리스너 = 플레이어 = 카메라
	GameObject* m_audioListener = nullptr;

	// 제대로 만든게 아니다
public:
	ID3DRenderer* m_renderer = nullptr;

};
