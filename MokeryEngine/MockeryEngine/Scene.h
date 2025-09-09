#pragma once
#include "framework.h"
#include "SceneEnum.h"

/// <summary>
/// ������Ʈ���� 
/// �ö󰡰� ��ȣ�ۿ��ϴ� ����
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

	// Scene�� �⺻������ �����Ѵ�.
	virtual void EditScene(EngineResourceManager* resourceManager, EngineObjectManager* objManager, TimeManager* timeManager, CollisionDetectManager* collisionDetectManager, PhysicsManager* physicsManager) abstract; // , InputManager* inputManger) abstract;	// scene�� ���۵� �� �Ͼ�� �ൿ�� �Ѵ�.
	
	virtual void Awake() abstract;
	virtual void Start() abstract;

	virtual void FixedUpdate(float dTime) abstract;

	// scene�� �����ϴ� ������Ʈ���� �ϰ� Update�Ѵ�.
	virtual void Update(float dTime) abstract;
	// ������ ���� �ι�° ������Ʈ
	virtual void LateUpdate(float dTime) abstract;
	// scene�� �����ϴ� ������Ʈ���� �ϰ� Render�Ѵ�.
	virtual void Render() abstract;
	// scene�� ��� ������Ʈ���� �����Ѵ�.
	virtual void End() abstract;
	// Scene�� �����̾ ���� ������Ʈ���� �����Ѵ�.
	virtual void EndLayer(unsigned int _layer) abstract;

	/// <summary>
	/// Get/Set
	/// </summary>
public:
	Scene* GetScene(){ return this; }

	ID3DRenderer* GetRenderer() const { return m_renderer; }
	void SetRenderer(ID3DRenderer* val) { m_renderer = val; }

	virtual SceneNumber GetSceneNum()abstract;

	// scene������ �� �ʿ���
	SceneManager* GetSceneManger() const { return m_sceneManager; }
	void SetSceneManger(SceneManager* val) { m_sceneManager = val; }

protected:
	// scene�� �����ϴ� ������Ʈ��
	std::vector<GameObject*> m_objects{};

	// ������Ʈ ������ ���� �ӽú���
	GameObject* m_object = nullptr;

	EngineObjectManager* m_objManager = nullptr;
	EngineResourceManager* m_resourceManager = nullptr;
	TimeManager* m_timeManager = nullptr;
	InputManager* m_inputManager = nullptr;
	SceneManager* m_sceneManager = nullptr;
	/*SoundManager* m_soundManager = nullptr;
	SoundManager::getInstance() = nullptr;*/

	// ����� ������ = �÷��̾� = ī�޶�
	GameObject* m_audioListener = nullptr;

	// ����� ����� �ƴϴ�
public:
	ID3DRenderer* m_renderer = nullptr;

};
