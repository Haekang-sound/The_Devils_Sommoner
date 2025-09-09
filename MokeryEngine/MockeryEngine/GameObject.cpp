#include "pch.h"
#include "GameObject.h"

// 매니저
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

// 오브젝트 id를 받아서 자식벡터로 추가한다.
// not 오브젝트 id-> 오브젝트 포인터
void GameObject::SetChild(GameObject* val)
{
	m_childs.push_back(val);
}

/// <summary>
/// 자식오브젝트를 id로 찾아내는 함수
/// </summary>
/// <param name="id">object id</param>
/// <returns></returns>
GameObject* GameObject::GetChildForID(int id)
{
	// child 벡터를 순회하고
	for (auto& e : m_childs)
	{
		// id가 같은 오브젝트를 찾으면
		if (e->GetObjectID() == id)
			// 반환한다.
			return e;
	}
	// 찾지못했다면 nullptr을 반환한다.
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
	// 벡터에 존재하는 컴포넌트들을 딜리트 시켜준다.
	for (auto& e : m_components)
	{
		// 컴포넌트 내부의 포인터를 해제한다.
		e->Release();
		// 컴포넌트를 해제한다.
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
