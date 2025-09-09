#pragma once
#include "framework.h"
#include "GameObject.h"



class Component;
class Scene;

/// <summary>
/// ������Ʈ�� �����ϰ� �ҷ����� �Ŵ���
/// </summary>
class EngineObjectManager

{
public:
	EngineObjectManager();
	~EngineObjectManager();
	
	void Init();
	void Release();							// ���ӿ�����Ʈ ���͸� ���� �����Ѵ�.
	void ReleaseLayer(unsigned int _layer);	// ���̾ ���� ������Ʈ ���� ������ �����Ѵ�.\

	void OffScene();
	void OnScene();

public:
	// ������Ʈ�� �����ϰ� ��ü�� ��ȯ�Ѵ�.
	GameObject* CreateObject();
	GameObject* GetObjectByName(std::string _name);
	template<typename T>
	GameObject* GetOBjectsByComponent();
	
	void SetParentByName(GameObject* _child, std::string _name);	// �̸����� �θ� ã�Ƽ� �߰��Ѵ�
	void SetChildByName(GameObject* _parent, std::string _name);	// �̸����� �ڽ��� ã�Ƽ� �߰��Ѵ�

	void SetParentByGameObject(GameObject* child, GameObject* parent);

	std::vector<GameObject*> GetObjects() const { return m_objects; }

private:
	int MakeObjectID();	// ObjectID�� �����Ѵ�.
	void StoreObject(GameObject* obj);

private:
	// ������ ������Ʈ���� ������Ʈ �Ŵ������� �����Ѵ�.
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
