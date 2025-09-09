#pragma once
#include "framework.h"
#include "GameObject.h"



class Component;
class Scene;

/// <summary>
/// 오브젝트를 저장하고 불러오는 매니저
/// </summary>
class EngineObjectManager

{
public:
	EngineObjectManager();
	~EngineObjectManager();
	
	void Init();
	void Release();							// 게임오브젝트 벡터를 전부 삭제한다.
	void ReleaseLayer(unsigned int _layer);	// 레이어에 따라 오브젝트 삭제 정도를 결정한다.\

	void OffScene();
	void OnScene();

public:
	// 오브젝트를 생성하고 객체를 반환한다.
	GameObject* CreateObject();
	GameObject* GetObjectByName(std::string _name);
	template<typename T>
	GameObject* GetOBjectsByComponent();
	
	void SetParentByName(GameObject* _child, std::string _name);	// 이름으로 부모를 찾아서 추가한다
	void SetChildByName(GameObject* _parent, std::string _name);	// 이름으로 자식을 찾아서 추가한다

	void SetParentByGameObject(GameObject* child, GameObject* parent);

	std::vector<GameObject*> GetObjects() const { return m_objects; }

private:
	int MakeObjectID();	// ObjectID를 생성한다.
	void StoreObject(GameObject* obj);

private:
	// 생성된 오브젝트들을 오브젝트 매니저에서 관리한다.
	std::vector<GameObject*> m_objects;

public:
	int id;
};

template<typename T>
GameObject* EngineObjectManager::GetOBjectsByComponent()
{
	for (auto e : m_objects)
	{
		T* _cam = e->GetComponent<T>();
		if (_cam != nullptr)
		{
			return e;
		}
	}
	return nullptr;

}
