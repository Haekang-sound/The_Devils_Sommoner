#pragma once
#include "Component.h"

// 그리기 위한  정보들을 갖고 있는 RenderComonent
class RenderComponent :	public Component
{
public:
	virtual void Start() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

	// Component을(를) 통해 상속됨
	void FixedUpdate(float dTime) override;
};

