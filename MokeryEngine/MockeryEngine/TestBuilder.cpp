#include "pch.h"
#include "TestBuilder.h"

void TestBuilder::Initialize(ResourceCreator* creator)
{
	// 여기서 데이터만들때 필요한 자료를 세팅한다 ^0^
}

void TestBuilder::CreateType(std::string fileName)
{

	// 여기서 데이터를 열심히 만들어 넣는다 ^^*

}

void TestBuilder::SetType(IResource* resource)
{
	resource->SetResource(m_type);
}
