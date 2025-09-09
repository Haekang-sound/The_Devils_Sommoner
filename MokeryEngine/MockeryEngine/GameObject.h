#pragma once
// ���ø� ��Ÿ
#include "framework.h"
#include "SceneEnum.h"
#include <type_traits>

/// <summary>
/// ������Ʈ�� ��� Entity Ŭ����
/// </summary>

class Component;
class Scene;
class ID3DRenderer;
class EngineObjectManager;
class CameraComponent;
class Collision;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Awake();
	void Start();
	void FixedUpdate(float dTime);
	void Update(float dTime);
	void LateUpdate(float dTime);
	void Render();


	// get,set
public:
	// �θ� �����ϰ� ã�´�.
 	GameObject* GetParent() const { return m_parents; }

	// ��� �� ����: ��¥ �θ� �������ְ� ���� ������ �����ϴ�.
 	void SetParent(GameObject* val) { m_parents = val; }
	void SetParentByName(std::string _name);
	void SetChildByName(std::string _name);
	
	void SetParentByGameObject(GameObject* val);

	// ������Ʈ �Ŵ����� �����Ѵ�.
	void SetObjManager(EngineObjectManager* val) { m_objManager = val; };
	EngineObjectManager* GetObjectManager() const { return m_objManager; }

	// �ڽ��� �����ϰ� ã�´�.
	void SetChild(GameObject* val);
	GameObject* GetChildForID(int id);

	// ������Ʈ �̸��� �����ϰ� ã�´�.
	std::string GetName() const { return m_name; }
	void SetName(std::string val) { m_name = val; }

	// id
	const unsigned int GetObjectID() const { return m_objectID; }
	void SetObjectID(const unsigned int val) { m_objectID = val; }

	// layer
	unsigned int GetLayer() const { return m_layer; }
	void SetLayer(unsigned int val) { m_layer = val; }

	// active;
	bool GetIsActive() const { return isActive; }
	void SetIsActive(bool val);// { isActive = val; }
	bool* GetIsDraw() { return &isDraw; }
	void SetIsDraw(bool val);

	void SetIsDrawRecursively(const bool& val);
private:

public:
	// ��ƼƼ�� ������Ʈ�� �߰��Ѵ�.
	template<typename T>
	T* AddComponent();

	template <typename T, typename First, typename... Rest>
	void AddComponent();
	
	// ���ϴ� ������Ʈ�� ��ȯ�Ѵ�.
	template<typename T>
	T* GetComponent();

	// ������Ʈ���� �����Ѵ�.
	void Release();

	template<typename T>
	T* GetComponentFromParent();

public:
	void OnCollisionEnter(Collision* collision);
	void OnCollisionStay(Collision* collision);
	void OnCollisionExit(Collision* collision);

public:
	bool isActive = true;
	bool isDraw = true;

private:
	// ������Ʈ ����
	unsigned int m_objectID;// id
	std::string m_name;		// �̸�

	Scene* m_scene;

	// ������Ʈ ���̾�
	unsigned int m_layer;	// ���������� ������ �� ���̾�

	// ������Ʈ�� ��Ƶδ� ����.
	std::vector<Component*> m_components;

	// �θ��� ������
	GameObject* m_parents;

	// �ڽ��� �����͵�
	std::vector<GameObject*> m_childs;

	EngineObjectManager* m_objManager;
};

// ������Ʈ �����͸� ��ȯ�ؼ� �޼��� ü�̴��� �� �� �ֵ��� �Ѵ�.
template<typename T>
T* GameObject::AddComponent()
{
	// ���� T(������Ʈ)�� ������Ʈ �������̽��� ��ӹް� �ִٸ�
	if (std::is_base_of_v<Component,T> == true)
		// T�� �����Ѵ�.
	{
		T* newComponent = new T;
		// �� ������Ʈ�� �ش� ������Ʈ�� �������� �����Ѵ�.
		newComponent->SetOwner(this);
		m_components.push_back(newComponent);
		return newComponent;
	}
	// �ƴ϶�� ������Ʈ�� �ƴ϶�� ��.
	else
	{
		// �̷��� ���°� �³�??
		//MessageBox(NULL,L"Component Error",L"Component Error",NULL);
		return nullptr;
	}
}

template <typename T, typename First, typename... Rest>
void GameObject::AddComponent()
{
	AddComponent<T>();
	AddComponent<First, Rest...>(); // �κ� Ư��ȭ�� ��� ȣ��
}

template<typename T>
T* GameObject::GetComponent()
{
	// ���͸� ��ȸ�ؼ�  
	for (auto& e : m_components)
	{
		T* component = dynamic_cast<T*>(e);
		// T*�� �����Ѵٸ� 
		if (component)
		{
			// T�� �ش��ϴ� ������Ʈ�� ��ȯ�Ѵ�.
			return component;
		}
	}
	// ���͸� ������ ��ȸ�ϸ� nullptr�� ��ȯ�Ѵ�.
	return nullptr;
	 
}

template<typename T>
inline T* GameObject::GetComponentFromParent()
{
	if (m_parents == nullptr)
	{
		return nullptr;
	}
	else
	{
		return m_parents->GetComponent<T>();
	}
}

