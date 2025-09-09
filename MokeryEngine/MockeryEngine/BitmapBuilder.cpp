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

	// �̸��� ��θ� �����ؼ� ���� ��θ� �ϼ��Ѵ�.
	std::wstring filepath = m_path + wFileName + m_extension;

	// �����Ѵ�.
	m_image->m_data = (fileName, reinterpret_cast<HBITMAP>(LoadImage(NULL, filepath.c_str(), IMAGE_BITMAP, 1000, 721, LR_LOADFROMFILE)));
}

void BitmapBuilder::SetType(IResource* resource)
{
	resource->SetResource(m_image);
}
