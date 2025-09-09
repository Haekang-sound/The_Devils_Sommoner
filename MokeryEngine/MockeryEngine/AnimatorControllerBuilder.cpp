#include "pch.h"
#include "AnimatorControllerBuilder.h"
#include "AnimatorController.h"

AnimatorControllerBuilder::AnimatorControllerBuilder()
	: m_animController(nullptr)
{

}

AnimatorControllerBuilder::~AnimatorControllerBuilder()
{

}

void AnimatorControllerBuilder::Initialize(ResourceCreator* creator)
{
}

void AnimatorControllerBuilder::CreateType(std::string fileName)
{
}

void AnimatorControllerBuilder::SetType(IResource* resource)
{
	resource->SetResource(m_animController);
}
