#pragma once
#include "framework.h"
#include "IResource.h"
#include "ResourceCreator.h"

class IBuilder
{
public:
	virtual ~IBuilder() {};

	virtual void Initialize(ResourceCreator* creator) abstract;
	
	// Ÿ���� �����Ѵ�.
	virtual void CreateType(std::string fileName) abstract;
	
	// IResource�� ������ �����Ѵ�.
	virtual void SetType(IResource* resource) abstract;

};