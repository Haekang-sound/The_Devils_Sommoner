#pragma once
#include "Image.h"
#include "IBuilder.h"
#include "ResourceCreator.h"


class BitmapBuilder : public IBuilder
{
public:
	BitmapBuilder();
	~BitmapBuilder();

	virtual void Initialize(ResourceCreator* creator )override;
	virtual void CreateType(std::string fileName) override;
	virtual void SetType(IResource* resource) override;

private:
	// ������ �����͸� �ӽú����ϴ� ����
	Image* m_image;
	
	// ���
	std::wstring m_path = L"../Demo/Content/Image/";	// ���ϰ��
	std::wstring m_extension = L".bmp";						// �ڷ���
};

