#pragma once
// 템플릿 메타
#include "framework.h"
#include "SceneEnum.h"
#include <type_traits>

/// <summary>
/// 컴포넌트를 담는 Entity 클래스
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
	// 부모를 세팅하고 찾는다.
 	GameObject* GetParent() const { return m_parents; }

	// 사용 시 주의: 진짜 부모만 설정해주고 내부 설정이 없습니다.
 	void SetParent(GameObject* val) { m_parents = val; }
	void SetParentByName(std::string _name);
	void SetChildByName(std::string _name);
	
	void SetParentByGameObject(GameObject* val);

	// 오브젝트 매니저를 세팅한다.
	void SetObjManager(EngineObjectManager* val) { m_objManager = val; };
	EngineObjectManager* GetObjectManager() const { return m_objManager; }

	// 자식을 세팅하고 찾는다.
	void SetChild(GameObject* val);
	GameObject* GetChildForID(int id);

	// 오브젝트 이름을 세팅하고 찾는다.
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
	// 엔티티에 컴포넌트를 추가한다.
	template<typename T>
	T* AddComponent();

	template <typename T, typename First, typename... Rest>
	void AddComponent();
	
	// 원하는 컴포넌트를 반환한다.
	template<typename T>
	T* GetComponent();

	// 컴포넌트들을 삭제한다.
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
	// 오브젝트 정보
	unsigned int m_objectID;// id
	std::string m_name;		// 이름

	Scene* m_scene;

	// 오브젝트 레이어
	unsigned int m_layer;	// 생성삭제의 기준이 될 레이어

	// 컴포넌트를 담아두는 벡터.
	std::vector<Component*> m_components;

	// 부모의 포인터
	GameObject* m_parents;

	// 자식의 포인터들
	std::vector<GameObject*> m_childs;

	EngineObjectManager* m_objManager;
};

// 컴포넌트 포인터를 반환해서 메서드 체이닝을 할 수 있도록 한다.
template<typename T>
T* GameObject::AddComponent()
{
	// 만약 T(컴포넌트)가 컴포넌트 인터페이스를 상속받고 있다면
	if (std::is_base_of_v<Component,T> == true)
		// T를 생성한다.
	{
		T* newComponent = new T;
		// 이 오브젝트를 해당 컴포넌트의 주인으로 설정한다.
		newComponent->SetOwner(this);
		m_components.push_back(newComponent);
		return newComponent;
	}
	// 아니라면 컴포넌트가 아니라는 것.
	else
	{
		// 이렇게 쓰는거 맞나??
		//MessageBox(NULL,L"Component Error",L"Component Error",NULL);
		return nullptr;
	}
}

template <typename T, typename First, typename... Rest>
void GameObject::AddComponent()
{
	AddComponent<T>();
	AddComponent<First, Rest...>(); // 부분 특수화된 재귀 호출
}

template<typename T>
T* GameObject::GetComponent()
{
	// 벡터를 순회해서  
	for (auto& e : m_components)
	{
		T* component = dynamic_cast<T*>(e);
		// T*가 존재한다면 
		if (component)
		{
			// T에 해당하는 컴포넌트를 반환한다.
			return component;
		}
	}
	// 벡터를 끝까지 순회하면 nullptr을 반환한다.
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

