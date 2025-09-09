#pragma once

enum class SceneNumber
{
	Title,

	Test,
	Select,
	Stage01,
	Stage02,
	Stage03,

	Ending
};

/// <summary>
/// 오브젝트들이 
/// 올라가고 상호작용하는 공간
/// </summary>

class KSL;
class ResourceManager;
class ObjectManager;
class TimeManager;
class InputManager;
class GameObject;
class ID3DRenderer;

class IScene
{
public:
	virtual ~IScene() {};

	// Scene의 기본정보를 편집한다.
	virtual void EditScene(ResourceManager* resourceManager, ObjectManager* objManager, TimeManager* timeManager, InputManager* inputManger) abstract;

	// scene이 시작될 때 일어나는 행동을 한다.
	virtual void Start() abstract;

	// scene에 존재하는 오브젝트들을 일괄 Update한다.
	virtual void Update(float dTime) abstract;

	// 정리를 위한 두번째 업데이트
	virtual void LateUpdate(float dTime) abstract;

	// scene에 존재하는 오브젝트들을 일괄 Render한다.
	virtual void Render() abstract;

	// scene의 오브젝트들을 해제한다.
	virtual void End() abstract;

	/// <summary>
	/// Get/Set
	/// </summary>
public:
	/// <summary>
	/// SceneNum 정보를 얻어온다.
	/// 이를 이용해서 필요한 씬을 찾는다.
	/// </summary>
	/// <returns></returns>
	SceneNumber GetSceneNumber() const { return m_SceneNum; }

	/// <summary>
	/// Scene Number를 세팅한다.
	/// </summary>
	/// <param name="val"></param>
	void SetSceneNumber(SceneNumber val) { m_SceneNum = val; }

	virtual void SetKSL(KSL* val)  abstract;

private:
	SceneNumber m_SceneNum{};

};
