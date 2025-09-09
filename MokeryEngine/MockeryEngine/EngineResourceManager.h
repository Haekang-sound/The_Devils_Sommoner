#pragma once
#include <string>
#include <vector>
#include <map>

#include "IResource.h"
#include "ResourceFactory.h"

class KSL;

/// <summary>
/// ���ҽ��� �����Ѵ�.
/// </summary>
class EngineResourceManager
{
public:
	EngineResourceManager();
	~EngineResourceManager();


	void Init(KSL* soundManager);

	// ���ҽ��� Load�Ѵ�.(+�����Ѵ�.)
	template<class T>
	void LoadResource(std::string fileName);

	// ���ҽ��� Get�Ѵ�.
	template<class T>
	Resource<T>* GetResource(std::string fileName);

	// ���ҽ��� �����Ѵ�.
	void Release();

	
public:
	// ���ϸ�� �߻�ȭ�� ���ҽ���ü�� �����·� �����Ѵ�.
	std::map <std::string, IResource*> m_resourceMap;

private:
	ResourceFactory* m_resourceFactory;
	ResourceCreator* m_creator;

};


/// LoadResource�� ������ �θ��� ���? 
/// ���� ���ҽ��� ��� �������� �ʿ��ϴ�
/// ������ �츮�� ���� �̸��� ���ҽ��� ����ϸ� �ȵȴ�! 
/// ������ ������ �ʿ��� ���ҽ��� ��ĥ���� �𸥴�! 
/// �����!! 
template<class T>
void EngineResourceManager::LoadResource(std::string fileName)
{ 
	m_resourceFactory->SetBuilder<T>();			// 1. ������ �����Ѵ�
	m_resourceFactory->Initialize(m_creator);	// 2. ������ �ʱ�ȭ �Ѵ�.
	m_resourceFactory->CreateResource<T>();		// 3. �ڷ����� �´� ���ҽ�<T>�� �����Ѵ�.
	m_resourceFactory->CreateType(fileName);	// 4. �����͸� �����ؼ� ���ҽ�<T>�� �ִ´� .
	
	m_resourceMap.emplace(fileName, m_resourceFactory->GetResource());// ���ҽ��� �����Ѵ�.

}

template<class T>
Resource<T>* EngineResourceManager::GetResource(std::string fileName)
{
	// ���ϸ����� �����͸� ã�� ĳ�����Ѵ�.
	Resource<T>* temp = dynamic_cast<Resource<T>*>(m_resourceMap[fileName]);
	
	// ĳ���ü��� ���θ� �Ǵ��ϰ� 
	if (temp != nullptr)
	{
		//�����ߴٸ� ��ȯ�Ѵ�.
		return dynamic_cast<Resource<T>*>(m_resourceMap[fileName]);
	}
	// �����ߴٸ� nullptr�� ��ȯ�Ѵ�.
	return nullptr;

}

