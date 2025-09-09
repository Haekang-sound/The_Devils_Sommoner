#pragma once
#include "Component.h"

/// <summary>
/// 2024.01.22 - ���Լ�
/// ���� Animation�� �����ϱ� ���� ������Ʈ�̴�
/// </summary>
class Animator : public Component
{
public:
	Animator();
	virtual ~Animator();


public:
	void Start() override;
	void FixedUpdate(float dTime) override;
	void Update(float dTime) override;
	void LateUpdate(float dTime) override;
	void Render() override;
	void Release() override;

};

