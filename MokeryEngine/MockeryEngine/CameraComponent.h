#pragma once
#include "Component.h"
#include "framework.h"

class ID3DRenderer;

class Transform;

class CameraComponent : public Component
{
public:
    CameraComponent();
    virtual ~CameraComponent();
    void Start() override;
    void FixedUpdate(float dTime) override;
    void Update(float dTime) override;
    void LateUpdate(float dTime) override;
    void Render() override;
    void Release() override;

    // get / set
public:
    unsigned int GetCameraID() const { return m_cameraID; }
    void SetCameraID(unsigned int val) { m_cameraID = val; }
    const SimpleMath::Matrix& GetView() { return m_View; }

public:
    void SetFov(int fov);


/// <summary>
/// 용준 작성
/// </summary>
    Transform* m_pTransform;
    Vector3 temp;

private:
    float m_power = 1.f;
    unsigned int m_cameraID = 0;
    SimpleMath::Matrix m_View;
    RenderMatrix44 m_RenderView;
};

