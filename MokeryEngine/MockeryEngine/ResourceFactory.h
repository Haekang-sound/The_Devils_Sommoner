#pragma once
#include <string>
#include <unordered_map>
#include <type_traits>

#include "Resource.h"

// 팩토리는 모든 빌더를 갖고 있어야 한다
#include "TestBuilder.h"
#include "AudioBuilder.h"
#include "BitmapBuilder.h"
#include "AnimationBuilder.h"
#include "AnimatorControllerBuilder.h"
#include "TileMapBuilder.h"
#include "FBXBuilder.h"

/// <summary>
/// 리소스를 생산한다.
/// </summary>
class ResourceFactory 
{
public:
	ResourceFactory();
	~ResourceFactory();

	// 리소스제작에 쓰이는 인자를 한번에 몰아넣은 우라늄 원석을 가져오자
	void Initialize(ResourceCreator* creator);

	// 데이터에 맞는 빌더를 세팅한다.
	template<typename T>
	bool FindBuilder();

	template <typename T>
	void SetBuilder();

	// 데이터를 담는 Resource<data> 자료형 생성
	template <typename T>
	void CreateResource();

	// 데이터를 생성한다.
	void CreateType(std::string fileName);

	// 리소스객체를 반환한다.
	IResource* GetResource();

private:
	// 현재 사용할 빌더
	IBuilder* currentBuilder;
	// 현재 만든 리소스
	IResource* m_resource;

};


template<typename T>
bool ResourceFactory::FindBuilder()
{
	// 빌더맵에서 해당 빌더를 찾는다.
	if (T::m_builder!=nullptr)
	{
		// 찾았다면
		return true;
	}

	//찾지 못했다면
	return false;
}

template <typename T>
void ResourceFactory::SetBuilder()
{
	// 빌더를 찾는다. 
	if (FindBuilder<T>())
	{
		// 빌더를 찾았다면 세팅한다.
		currentBuilder = T::m_builder;
		return;
	}
	else
	{
		// 빌더를 찾지못하면 
		// 생성하고 저장한다
		T::m_builder = new std::remove_reference_t<decltype(*T::m_builder)>();
		// 그리고 세팅한다.
		currentBuilder = T::m_builder;
	}

}

template <typename T>
void ResourceFactory::CreateResource()
{
	// 리소스를 만든다
	m_resource = new Resource<T>();
}

