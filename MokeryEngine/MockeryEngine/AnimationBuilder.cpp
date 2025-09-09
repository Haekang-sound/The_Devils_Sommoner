#include "pch.h"
#include "AnimationBuilder.h"

AnimationBuilder::AnimationBuilder()
	:m_animation(nullptr)
{

}

AnimationBuilder::~AnimationBuilder()
{

}

void AnimationBuilder::Initialize(ResourceCreator* creator)
{
}

void AnimationBuilder::CreateType(std::string fileName)
{
}

void AnimationBuilder::SetType(IResource* resource)
{
	resource->SetResource(m_animation);
}
