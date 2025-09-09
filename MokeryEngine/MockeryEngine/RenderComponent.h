#pragma once
#include "Component.h"

// �׸��� ����  �������� ���� �ִ� RenderComonent
class RenderComponent :	public Component
{
public:
	virtual void Start() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

	// Component��(��) ���� ��ӵ�
	void FixedUpdate(float dTime) override;
};

