#pragma once
#include "IBuilder.h"

class FBX;

class FBXBuilder :  public IBuilder
{
public:
	FBXBuilder();
	~FBXBuilder();
	// IBuilder을(를) 통해 상속됨
	void Initialize(ResourceCreator* creator) override;
	void CreateType(std::string fileName) override;
	void SetType(IResource* resource) override;

private:
	FBX* m_fbx;
	std::wstring m_dirPathW = L"../Resources/FBX/";
	std::string m_dirPath = "../Resources/FBX/";
	std::wstring m_extensionW = L".fbx";
	std::string m_extension = ".fbx";
};

