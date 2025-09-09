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
	// 생성된 데이터를 임시보관하는 변수
	Image* m_image;
	
	// 경로
	std::wstring m_path = L"../Demo/Content/Image/";	// 파일경로
	std::wstring m_extension = L".bmp";						// 자료형
};

