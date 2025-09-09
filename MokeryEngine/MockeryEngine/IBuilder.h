#pragma once
#include "framework.h"
#include "IResource.h"
#include "ResourceCreator.h"

class IBuilder
{
public:
	virtual ~IBuilder() {};

	virtual void Initialize(ResourceCreator* creator) abstract;
	
	// 타입을 생성한다.
	virtual void CreateType(std::string fileName) abstract;
	
	// IResource에 파일을 세팅한다.
	virtual void SetType(IResource* resource) abstract;

};