#include "pch.h"
#include "Animation.h"
#include "AnimationBuilder.h"

AnimationBuilder* Animation::m_builder = nullptr;

Animation::Animation()
	: m_path()
{

}

Animation::~Animation()
{

}

void Animation::LoadAnimation(const std::string& path)
{
	// ���� �ҷ��´�. 
	// Graphics���� �� ����� Animation�� Load���ּ��� ! �ؾ��ϳ�
}
