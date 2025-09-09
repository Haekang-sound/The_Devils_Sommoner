#include "pch.h"
#include "BitmapBuilder.h"

BitmapBuilder::BitmapBuilder()
	: m_image(nullptr)
{

}

BitmapBuilder::~BitmapBuilder()
{

}

void BitmapBuilder::Initialize(ResourceCreator* creator)
{
}

void BitmapBuilder::CreateType(std::string fileName)
{

	m_image = new Image();
	std::wstring wFileName;

	wFileName.assign(fileName.begin(), fileName.end());

	// 이름과 경로를 조합해서 파일 경로를 완성한다.
	std::wstring filepath = m_path + wFileName + m_extension;

	// 저장한다.
	m_image->m_data = (fileName, reinterpret_cast<HBITMAP>(LoadImage(NULL, filepath.c_str(), IMAGE_BITMAP, 1000, 721, LR_LOADFROMFILE)));
}

void BitmapBuilder::SetType(IResource* resource)
{
	resource->SetResource(m_image);
}
