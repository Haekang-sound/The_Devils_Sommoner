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
	// 뭔가 불러온다. 
	// Graphics에서 이 경로의 Animation을 Load해주세요 ! 해야하나
}
