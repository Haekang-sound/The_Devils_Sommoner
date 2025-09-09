#pragma once
#include "IResource.h"

template <typename T>
class Resource : public IResource
{
public:
	virtual void SetResource(void* Handle) override;
	virtual void ReleaseResource() override;
	T* m_type{};
private:

};

template <typename T>
void Resource<T>::SetResource(void* Handle)
{
	m_type = reinterpret_cast<T*>(Handle);
}

template <typename T>
void Resource<T>::ReleaseResource()
{
	// 리소스가 남아있다면
	if (m_type != nullptr)
	{
		if (m_type->m_builder != nullptr)
		{
			delete m_type->m_builder;
			m_type->m_builder = nullptr;
		}
		delete m_type;
		m_type = nullptr;
	}
}