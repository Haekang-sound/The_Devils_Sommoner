#include "pch.h"
#include "EngineObjectManager.h"

// o트랜스폼헤더를 포함한다.
#include "Transform.h"

EngineObjectManager::EngineObjectManager()
{

}

EngineObjectManager::~EngineObjectManager()
{

}

void EngineObjectManager::Init()
{

}

void EngineObjectManager::Release()
{
	for (auto& e : m_objects)
	{
		e->Release();

		delete e;
	}

	m_objects.clear();
}

/// <summary>
/// 레이어단위로 오브젝트를 정리하기 위한 함수
/// </summary>
/// <param name="_layer">다음 Scene의 레이어</param>
void EngineObjectManager::ReleaseLayer(unsigned int _layer)
{
	// 오브젝트 벡터를 순회한다
	for (auto& e : m_objects)
	{
		// 오브젝트 레이어가 다음 레이어 보다 낮다면
		if(e->GetLayer() < _layer)
		{
			// 해당 오브젝트는 삭제한다.
			e->Release();

			delete e;
			e = nullptr;
		}
	}
	m_objects.clear();

	// 지워진 오브젝트들을 삭제한다
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), nullptr), m_objects.end());

}

void EngineObjectManager::OffScene()
{
	for (auto& e : m_objects)
	{
		e->SetIsActive(false);
		e->SetIsDrawRecursively(false);
	}
}

void EngineObjectManager::OnScene()
{
	for (auto& e : m_objects)
	{
		e->SetIsActive(true);
		e->SetIsDrawRecursively(true);
	}
}

GameObject* EngineObjectManager::CreateObject()
{
	GameObject* _gameobj = new GameObject();	// 오브젝트 생성
	_gameobj->SetObjManager(this);
	_gameobj->AddComponent<Transform>();		// 기본적으로 트랜스폼을 붙여준다
	_gameobj->SetObjectID(MakeObjectID());	// 오브젝트 id 입력
	StoreObject(_gameobj);					// 생성된 오브젝트 저장

	return _gameobj;
};

/// <summary>
/// 이름으로 오브젝트를 찾는다.
/// </summary>
/// <param name="_name"></param>
GameObject* EngineObjectManager::GetObjectByName(std::string _name)
{
	// 갖고 있는 오브젝트들을 순회한다.
	for (auto& e : m_objects)
	{
		// 이름이 같은 오브젝트를 찾았다면
		if (e->GetName() == _name)
		{
			// 반환한다.
			return e;
		}
	}
	// 찾지못했다면 nullptr을 반환한다.
	return nullptr;
}

// 이름을 통해 부모를 설정한다.
void EngineObjectManager::SetParentByName(GameObject* _child, std::string _name)
{
// 	// 부모없애기
	if ("null" == _name)
	{
		// 부모 오브젝트를 설정한다.
		_child->SetParent(nullptr);

		_child->GetComponent<Transform>()->SetParent(nullptr);

		return;
	}

	// 부모 오브젝트를 받아온다.
	GameObject* _parent = GetObjectByName(_name);

	// 부모 오브젝트를 설정한다.
	_child->SetParent(_parent);

	// 자식에 담는다.
	_parent->SetChild(_child);

	// 부모트랜스폼을 설정한다.
	_child->GetComponent<Transform>()->SetParent(_parent->GetComponent<Transform>());

	// 자식트랜스폼에 추가한다.
	_parent->GetComponent<Transform>()->AddChild(_child->GetComponent<Transform>());

	// 자식의 로컬에 부모의 월드를 세팅한다.
	//_child->GetComponent<Transform>()->SetLocal(_parent->GetComponent<Transform>()->GetWorld());

	_parent->GetComponent<Transform>()->UpdateTransform();
}

void EngineObjectManager::SetChildByName(GameObject* _parent, std::string _name)
{
	// 부모 오브젝트를 받아온다.
	GameObject* _child = GetObjectByName(_name);

	// 부모 오브젝트를 설정한다.
	_child->SetParent(_parent);

	// 자식에 담는다.
	_parent->SetChild(_child);

	// 부모트랜스폼을 설정한다.
	_child->GetComponent<Transform>()->SetParent(_parent->GetComponent<Transform>());

	// 자식트랜스폼에 추가한다.
	_parent->GetComponent<Transform>()->AddChild(_child->GetComponent<Transform>());

	// 자식의 로컬에 부모의 월드를 세팅한다.
	_child->GetComponent<Transform>()->SetLocal(_parent->GetComponent<Transform>()->GetWorld());

	_parent->GetComponent<Transform>()->UpdateTransform();
}

void EngineObjectManager::SetParentByGameObject(GameObject* child, GameObject* parent)
{
	if (parent == nullptr)
	{
		child->SetParent(nullptr);
		child->GetComponent<Transform>()->SetParent(nullptr);
		//child->GetComponent<Transform>()->SetWorld(GetObjectByName())
		return;
	}

	child->SetParent(parent);
	parent->SetChild(child);

	child->GetComponent<Transform>()->SetParent(parent->GetComponent<Transform>());
	parent->GetComponent<Transform>()->AddChild(child->GetComponent<Transform>());

	parent->GetComponent<Transform>()->UpdateTransform();
}

// 오브젝트의 id를 생성하는 무언가.
// 알고리즘이 강화되면 더 좋겠지만 일단은 id가 존재하는게 우선이므로 하나씩 늘린다.
int EngineObjectManager::MakeObjectID()
{
	//static int id = 0;

	return id++;

}

// 오브젝트를 오브젝트매니저가 관리하기 위해 벡터에 저장한다.
void EngineObjectManager::StoreObject(GameObject* obj)
{
	m_objects.push_back(obj);
}


