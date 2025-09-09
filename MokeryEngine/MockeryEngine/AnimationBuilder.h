#pragma once
#include "IBuilder.h"
#include "Animation.h"

/// <summary>
/// Animation을 만들기 위한 빌더가 아닐까?
/// 2024.01.22 - 강규석이 만들었어요.
/// </summary>
class AnimationBuilder : public IBuilder
{
public:
	AnimationBuilder();
	virtual ~AnimationBuilder();
public:
	void Initialize(ResourceCreator* creator) override;
	void CreateType(std::string fileName) override;
	void SetType(IResource* resource) override;

private:
	Animation* m_animation;
};

