#pragma once
#include "Component.h"


/// <summary>
/// ����� ������
/// �÷��̾�(ī�޶�)�� �پ� 3D ������ �����ʸ� ���ϴ� ������Ʈ
/// ������ �ϳ��� ��� ���� ������
/// 
/// 2024. 02. 15
/// </summary>
class AudioListener : public Component
{
public:
	AudioListener();
	~AudioListener();
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

};

