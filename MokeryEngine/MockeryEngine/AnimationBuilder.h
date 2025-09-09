#pragma once
#include "IBuilder.h"
#include "Animation.h"

/// <summary>
/// Animation�� ����� ���� ������ �ƴұ�?
/// 2024.01.22 - ���Լ��� ��������.
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

