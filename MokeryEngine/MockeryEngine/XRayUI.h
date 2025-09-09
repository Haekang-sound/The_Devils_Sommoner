#pragma once
#include "Component.h"
#include "framework.h"

class Transform;
class ItemChest;
class XRayUI : public Component
{
public:
	XRayUI();
	virtual ~XRayUI();
	// Component을(를) 통해 상속됨
	virtual void Start() override;
	virtual void FixedUpdate(float dTime) override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	virtual void Render() override;
	virtual void Release() override;

public:
// 	1. 제단위치에 카메라 역행렬을 곱한다.
//		제단위치를 알아야 한다
// 	2. 제단의 좌표를 z값으로 나눈다.
// 	3. 카메라행렬을 곱한다.

private:
	std::vector<ItemChest*> m_itemChests;

private:
	Transform* m_camTransform;
	Transform* m_alterTransform;

	unsigned int assetNum = 200;
	Vector2 m_size = {50.f, 50.f};
	unsigned int m_state = 0;

	SimpleMath::Matrix m_worldTM = m_worldTM.Identity;
	SimpleMath::Matrix m_proj = m_worldTM.Identity;
	SimpleMath::Matrix m_screen = m_worldTM.Identity;


};

