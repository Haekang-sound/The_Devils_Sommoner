#pragma once
#include <string>
#include <unordered_map>
#include <type_traits>

#include "Resource.h"

// ���丮�� ��� ������ ���� �־�� �Ѵ�
#include "TestBuilder.h"
#include "AudioBuilder.h"
#include "BitmapBuilder.h"
#include "AnimationBuilder.h"
#include "AnimatorControllerBuilder.h"
#include "TileMapBuilder.h"
#include "FBXBuilder.h"

/// <summary>
/// ���ҽ��� �����Ѵ�.
/// </summary>
class ResourceFactory 
{
public:
	ResourceFactory();
	~ResourceFactory();

	// ���ҽ����ۿ� ���̴� ���ڸ� �ѹ��� ���Ƴ��� ��� ������ ��������
	void Initialize(ResourceCreator* creator);

	// �����Ϳ� �´� ������ �����Ѵ�.
	template<typename T>
	bool FindBuilder();

	template <typename T>
	void SetBuilder();

	// �����͸� ��� Resource<data> �ڷ��� ����
	template <typename T>
	void CreateResource();

	// �����͸� �����Ѵ�.
	void CreateType(std::string fileName);

	// ���ҽ���ü�� ��ȯ�Ѵ�.
	IResource* GetResource();

private:
	// ���� ����� ����
	IBuilder* currentBuilder;
	// ���� ���� ���ҽ�
	IResource* m_resource;

};


template<typename T>
bool ResourceFactory::FindBuilder()
{
	// �����ʿ��� �ش� ������ ã�´�.
	if (T::m_builder!=nullptr)
	{
		// ã�Ҵٸ�
		return true;
	}

	//ã�� ���ߴٸ�
	return false;
}

template <typename T>
void ResourceFactory::SetBuilder()
{
	// ������ ã�´�. 
	if (FindBuilder<T>())
	{
		// ������ ã�Ҵٸ� �����Ѵ�.
		currentBuilder = T::m_builder;
		return;
	}
	else
	{
		// ������ ã�����ϸ� 
		// �����ϰ� �����Ѵ�
		T::m_builder = new std::remove_reference_t<decltype(*T::m_builder)>();
		// �׸��� �����Ѵ�.
		currentBuilder = T::m_builder;
	}

}

template <typename T>
void ResourceFactory::CreateResource()
{
	// ���ҽ��� �����
	m_resource = new Resource<T>();
}

