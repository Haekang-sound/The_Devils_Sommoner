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
	//Ÿ�� ����
	m_fbx = new FBX();

	// ������ ����
// 	std::wstring wFileName;     
// 	wFileName.assign(fileName.begin(), fileName.end());   

	// �����͸� Ÿ�Կ� ����
	//m_fbx->FBXPath = m_dirPath + wFileName + m_extension;
	m_fbx->FBXPath = m_dirPath + fileName + m_extension;
}

void FBXBuilder::SetType(IResource* resource)
{
	resource->SetResource(m_fbx);
}
