#pragma once
class IResource
{
public:
	virtual ~IResource() {};
	virtual void SetResource(void* Handle) abstract;
	virtual void ReleaseResource()abstract;
};
