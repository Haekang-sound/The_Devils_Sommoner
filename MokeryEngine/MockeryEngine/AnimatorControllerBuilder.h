#pragma once
#include "IBuilder.h"
#include "AnimatorController.h"

/// <summary>
/// animator controller¸¦ À§ÇÑ ºô´õ°¡ ¾Æ´Ò±î
/// </summary>
class AnimatorControllerBuilder : public IBuilder
{
public:
	AnimatorControllerBuilder();
	virtual ~AnimatorControllerBuilder();

public:
	void Initialize(ResourceCreator* creator) override;
	void CreateType(std::string fileName) override;
	void SetType(IResource* resource) override;

public:
	AnimatorController* m_animController;
};

