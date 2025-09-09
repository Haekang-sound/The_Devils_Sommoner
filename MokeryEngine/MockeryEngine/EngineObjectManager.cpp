#include "pch.h"
#include "EngineObjectManager.h"

// oƮ����������� �����Ѵ�.
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
/// ���̾������ ������Ʈ�� �����ϱ� ���� �Լ�
/// </summary>
/// <param name="_layer">���� Scene�� ���̾�</param>
void EngineObjectManager::ReleaseLayer(unsigned int _layer)
{
	// ������Ʈ ���͸� ��ȸ�Ѵ�
	for (auto& e : m_objects)
	{
		// ������Ʈ ���̾ ���� ���̾� ���� ���ٸ�
		if(e->GetLayer() < _layer)
		{
			// �ش� ������Ʈ�� �����Ѵ�.
			e->Release();

			delete e;
			e = nullptr;
		}
	}
	m_objects.clear();

	// ������ ������Ʈ���� �����Ѵ�
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
	GameObject* _gameobj = new GameObject();	// ������Ʈ ����
	_gameobj->SetObjManager(this);
	_gameobj->AddComponent<Transform>();		// �⺻������ Ʈ�������� �ٿ��ش�
	_gameobj->SetObjectID(MakeObjectID());	// ������Ʈ id �Է�
	StoreObject(_gameobj);					// ������ ������Ʈ ����

	return _gameobj;
};

/// <summary>
/// �̸����� ������Ʈ�� ã�´�.
/// </summary>
/// <param name="_name"></param>
GameObject* EngineObjectManager::GetObjectByName(std::string _name)
{
	// ���� �ִ� ������Ʈ���� ��ȸ�Ѵ�.
	for (auto& e : m_objects)
	{
		// �̸��� ���� ������Ʈ�� ã�Ҵٸ�
		if (e->GetName() == _name)
		{
			// ��ȯ�Ѵ�.
			return e;
		}
	}
	// ã�����ߴٸ� nullptr�� ��ȯ�Ѵ�.
	return nullptr;
}

// �̸��� ���� �θ� �����Ѵ�.
void EngineObjectManager::SetParentByName(GameObject* _child, std::string _name)
{
// 	// �θ���ֱ�
	if ("null" == _name)
	{
		// �θ� ������Ʈ�� �����Ѵ�.
		_child->SetParent(nullptr);

		_child->GetComponent<Transform>()->SetParent(nullptr);

		return;
	}

	// �θ� ������Ʈ�� �޾ƿ´�.
	GameObject* _parent = GetObjectByName(_name);

	// �θ� ������Ʈ�� �����Ѵ�.
	_child->SetParent(_parent);

	// �ڽĿ� ��´�.
	_parent->SetChild(_child);

	// �θ�Ʈ�������� �����Ѵ�.
	_child->GetComponent<Transform>()->SetParent(_parent->GetComponent<Transform>());

	// �ڽ�Ʈ�������� �߰��Ѵ�.
	_parent->GetComponent<Transform>()->AddChild(_child->GetComponent<Transform>());

	// �ڽ��� ���ÿ� �θ��� ���带 �����Ѵ�.
	//_child->GetComponent<Transform>()->SetLocal(_parent->GetComponent<Transform>()->GetWorld());

	_parent->GetComponent<Transform>()->UpdateTransform();
}

void EngineObjectManager::SetChildByName(GameObject* _parent, std::string _name)
{
	// �θ� ������Ʈ�� �޾ƿ´�.
	GameObject* _child = GetObjectByName(_name);

	// �θ� ������Ʈ�� �����Ѵ�.
	_child->SetParent(_parent);

	// �ڽĿ� ��´�.
	_parent->SetChild(_child);

	// �θ�Ʈ�������� �����Ѵ�.
	_child->GetComponent<Transform>()->SetParent(_parent->GetComponent<Transform>());

	// �ڽ�Ʈ�������� �߰��Ѵ�.
	_parent->GetComponent<Transform>()->AddChild(_child->GetComponent<Transform>());

	// �ڽ��� ���ÿ� �θ��� ���带 �����Ѵ�.
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

// ������Ʈ�� id�� �����ϴ� ����.
// �˰����� ��ȭ�Ǹ� �� �������� �ϴ��� id�� �����ϴ°� �켱�̹Ƿ� �ϳ��� �ø���.
int EngineObjectManager::MakeObjectID()
{
	//static int id = 0;

	return id++;

}

// ������Ʈ�� ������Ʈ�Ŵ����� �����ϱ� ���� ���Ϳ� �����Ѵ�.
void EngineObjectManager::StoreObject(GameObject* obj)
{
	m_objects.push_back(obj);
}


