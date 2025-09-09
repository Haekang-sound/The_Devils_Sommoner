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
/// ������Ʈ���� 
/// �ö󰡰� ��ȣ�ۿ��ϴ� ����
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

	// Scene�� �⺻������ �����Ѵ�.
	virtual void EditScene(ResourceManager* resourceManager, ObjectManager* objManager, TimeManager* timeManager, InputManager* inputManger) abstract;

	// scene�� ���۵� �� �Ͼ�� �ൿ�� �Ѵ�.
	virtual void Start() abstract;

	// scene�� �����ϴ� ������Ʈ���� �ϰ� Update�Ѵ�.
	virtual void Update(float dTime) abstract;

	// ������ ���� �ι�° ������Ʈ
	virtual void LateUpdate(float dTime) abstract;

	// scene�� �����ϴ� ������Ʈ���� �ϰ� Render�Ѵ�.
	virtual void Render() abstract;

	// scene�� ������Ʈ���� �����Ѵ�.
	virtual void End() abstract;

	/// <summary>
	/// Get/Set
	/// </summary>
public:
	/// <summary>
	/// SceneNum ������ ���´�.
	/// �̸� �̿��ؼ� �ʿ��� ���� ã�´�.
	/// </summary>
	/// <returns></returns>
	SceneNumber GetSceneNumber() const { return m_SceneNum; }

	/// <summary>
	/// Scene Number�� �����Ѵ�.
	/// </summary>
	/// <param name="val"></param>
	void SetSceneNumber(SceneNumber val) { m_SceneNum = val; }

	virtual void SetKSL(KSL* val)  abstract;

private:
	SceneNumber m_SceneNum{};

};
