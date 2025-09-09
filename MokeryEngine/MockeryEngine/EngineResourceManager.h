#pragma once
#include <string>
#include <vector>
#include <map>

#include "IResource.h"
#include "ResourceFactory.h"

class KSL;

/// <summary>
/// 리소스를 관리한다.
/// </summary>
class EngineResourceManager
{
public:
	EngineResourceManager();
	~EngineResourceManager();


	void Init(KSL* soundManager);

	// 리소스를 Load한다.(+저장한다.)
	template<class T>
	void LoadResource(std::string fileName);

	// 리소스를 Get한다.
	template<class T>
	Resource<T>* GetResource(std::string fileName);

	// 리소스를 해제한다.
	void Release();

	
public:
	// 파일명과 추상화된 리소스객체를 맵형태로 저장한다.
	std::map <std::string, IResource*> m_resourceMap;

private:
	ResourceFactory* m_resourceFactory;
	ResourceCreator* m_creator;

};


/// LoadResource로 빌더를 부르면 어떨까? 
/// 같은 리소스일 경우 방어수단이 필요하다
/// 하지만 우리는 같은 이름의 리소스를 사용하면 안된다! 
/// 하지만 씬마다 필요한 리소스가 겹칠지도 모른다! 
/// 어떡하지!! 
template<class T>
void EngineResourceManager::LoadResource(std::string fileName)
{ 
	m_resourceFactory->SetBuilder<T>();			// 1. 빌더를 세팅한다
	m_resourceFactory->Initialize(m_creator);	// 2. 빌더를 초기화 한다.
	m_resourceFactory->CreateResource<T>();		// 3. 자료형에 맞는 리소스<T>를 생성한다.
	m_resourceFactory->CreateType(fileName);	// 4. 데이터를 생성해서 리소스<T>에 넣는다 .
	
	m_resourceMap.emplace(fileName, m_resourceFactory->GetResource());// 리소스를 저장한다.

}

template<class T>
Resource<T>* EngineResourceManager::GetResource(std::string fileName)
{
	// 파일명으로 데이터를 찾고 캐스팅한다.
	Resource<T>* temp = dynamic_cast<Resource<T>*>(m_resourceMap[fileName]);
	
	// 캐스팅성공 여부를 판단하고 
	if (temp != nullptr)
	{
		//성공했다면 반환한다.
		return dynamic_cast<Resource<T>*>(m_resourceMap[fileName]);
	}
	// 실패했다면 nullptr을 반환한다.
	return nullptr;

}

