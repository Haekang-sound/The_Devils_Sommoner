#include "pch.h"
#include "GameObject.h"

// �Ŵ���
#include "EngineObjectManager.h"

#include "Component.h"
#include "Collision.h"

GameObject::GameObject()
	:m_components{},
	m_objManager(nullptr),
	m_parents(nullptr), m_childs{},
	m_objectID(), m_name(), m_layer(0)
{

}

GameObject::~GameObject()
{

}

void GameObject::Awake()
{
	for (auto& e : m_components)
	{
		e->Awake();
	}
}

void GameObject::Start()
{
	for (auto& e : m_components)
	{
		e->Start();
	}

}

void GameObject::FixedUpdate(float dTime)
{
	if (isActive)
	{
		for (auto& e : m_components)
		{
			e->FixedUpdate(dTime);
		}
	}
}

void GameObject::Update(float dTime)
{
	if (isActive)
	{
		for (auto& e : m_components)
		{
			e->Update(dTime);
		}
	}
}

void GameObject::LateUpdate(float dTime)
{
	if (isActive)
	{
		for (auto e : m_components)
		{
			e->LateUpdate(dTime);
		}
	}
}

void GameObject::Render()
{
	// if (isDraw)
	if (isActive)
	{
		for (auto& e : m_components)
		{
			e->Render();
		}
	}
}

void GameObject::SetParentByName(std::string _name)
{
	m_objManager->SetParentByName(this, _name);
}

void GameObject::SetChildByName(std::string _name)
{
	m_objManager->SetChildByName(this, _name);
}

void GameObject::SetParentByGameObject(GameObject* val)
{
	m_objManager->SetParentByGameObject(this, val);
}

// ������Ʈ id�� �޾Ƽ� �ڽĺ��ͷ� �߰��Ѵ�.
// not ������Ʈ id-> ������Ʈ ������
void GameObject::SetChild(GameObject* val)
{
	m_childs.push_back(val);
}

/// <summary>
/// �ڽĿ�����Ʈ�� id�� ã�Ƴ��� �Լ�
/// </summary>
/// <param name="id">object id</param>
/// <returns></returns>
GameObject* GameObject::GetChildForID(int id)
{
	// child ���͸� ��ȸ�ϰ�
	for (auto& e : m_childs)
	{
		// id�� ���� ������Ʈ�� ã����
		if (e->GetObjectID() == id)
			// ��ȯ�Ѵ�.
			return e;
	}
	// ã�����ߴٸ� nullptr�� ��ȯ�Ѵ�.
	return nullptr;
}

void GameObject::SetIsActive(bool val)
{
	isActive = val;
	if (m_childs.size())
	{
		for (auto& e : m_childs)
		{
			e->SetIsActive(val);
		}
	}
}

void GameObject::SetIsDrawRecursively(const bool& val)
{
	SetIsDraw(val);

	for (auto c : m_childs)
	{
		c->SetIsDrawRecursively(val);
	}

	if (m_parents != nullptr)
		m_parents->SetIsDraw(val);

	/*isDraw = val;
	for (auto c : m_childs)
	{
		c->SetIsDraw(val);
	}*/
}

void GameObject::SetIsDraw(bool val)
{
	isDraw = val;
}

void GameObject::Release()
{
	// ���Ϳ� �����ϴ� ������Ʈ���� ����Ʈ �����ش�.
	for (auto& e : m_components)
	{
		// ������Ʈ ������ �����͸� �����Ѵ�.
		e->Release();
		// ������Ʈ�� �����Ѵ�.
		delete e;
		e = nullptr;
	}
	m_components.clear();
}

void GameObject::OnCollisionEnter(Collision* collision)
{
	for (auto& e : m_components)
	{
		e->OnCollisionEnter(collision);
	}
}

void GameObject::OnCollisionStay(Collision* collision)
{
	for (auto& e : m_components)
	{
		e->OnCollisionStay(collision);
	}
}

void GameObject::OnCollisionExit(Collision* collision)
{
	for (auto& e : m_components)
	{
		e->OnCollisionExit(collision);
	}
}
