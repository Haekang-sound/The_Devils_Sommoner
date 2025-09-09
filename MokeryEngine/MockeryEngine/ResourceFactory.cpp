#include "pch.h"
#include "ResourceFactory.h"

ResourceFactory::ResourceFactory()
	:m_resource(nullptr),  currentBuilder(nullptr)
{
}

ResourceFactory::~ResourceFactory()
{

}

void ResourceFactory::Initialize(ResourceCreator* creator)
{
	currentBuilder->Initialize(creator);
}

void ResourceFactory::CreateType(std::string fileName)
{
	// 데이터 타입을 생성한다.
	currentBuilder->CreateType(fileName);

	// 생성한 데이터를 리소스에 세팅한다.
	currentBuilder->SetType(m_resource);
}

IResource* ResourceFactory::GetResource()
{
	// 리소스의 생성 여부를 확인하고 
	if (m_resource != nullptr)
	{
		// 반환한다.
		return m_resource;
	}
	// 생성되지 않았다면 nullptr
	return nullptr;
}

