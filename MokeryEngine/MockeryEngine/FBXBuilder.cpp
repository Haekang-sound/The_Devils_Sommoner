#include "pch.h"
#include "FBXBuilder.h"
#include "FBX.h"

FBXBuilder::FBXBuilder()
	:m_fbx(nullptr)
{
}

FBXBuilder::~FBXBuilder()
{
}

void FBXBuilder::Initialize(ResourceCreator* creator)
{
}

void FBXBuilder::CreateType(std::string fileName)
{
	//타입 생성
	m_fbx = new FBX();

	// 데이터 생성
// 	std::wstring wFileName;     
// 	wFileName.assign(fileName.begin(), fileName.end());   

	// 데이터를 타입에 세팅
	//m_fbx->FBXPath = m_dirPath + wFileName + m_extension;
	m_fbx->FBXPath = m_dirPath + fileName + m_extension;
}

void FBXBuilder::SetType(IResource* resource)
{
	resource->SetResource(m_fbx);
}
