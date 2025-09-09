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
	// ������ Ÿ���� �����Ѵ�.
	currentBuilder->CreateType(fileName);

	// ������ �����͸� ���ҽ��� �����Ѵ�.
	currentBuilder->SetType(m_resource);
}

IResource* ResourceFactory::GetResource()
{
	// ���ҽ��� ���� ���θ� Ȯ���ϰ� 
	if (m_resource != nullptr)
	{
		// ��ȯ�Ѵ�.
		return m_resource;
	}
	// �������� �ʾҴٸ� nullptr
	return nullptr;
}

